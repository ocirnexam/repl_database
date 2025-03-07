#include "pager.h"

Pager* pager_open(const char* filename)
{
    int fd = open(filename,
                  O_RDWR |  // READ WRITE MODE
                  O_CREAT,  // Create file if it doesn't exist
                  S_IWUSR | // user write permission
                  S_IRUSR); // user read permission
    if (fd == -1)
    {
        printf("Unable to read file!\n");
        exit(EXIT_FAILURE);
    }

    off_t file_length = lseek(fd, 0, SEEK_END);

    Pager* pager = malloc(sizeof(Pager));
    pager->file_descriptor = fd;
    pager->file_length = file_length;
    pager->num_pages = (file_length / PAGE_SIZE);

    if(file_length % PAGE_SIZE != 0)
    {
        printf("DB file is not a whole number of pages! File is corrupted!\n");
        exit(EXIT_FAILURE);
    }

    for(uint32_t i = 0; i < TABLE_MAX_PAGES; i++)
    {
        pager->pages[i] = NULL;
    }
    return pager;
}

void* pager_get_page(Pager* pager, uint32_t page_num)
{
    if (page_num > TABLE_MAX_PAGES)
    {
        printf("Tried to fetch page out of bounds (%d).\n", page_num);
        exit(EXIT_FAILURE);
    }
    if (pager->pages[page_num] == NULL)
    {
        // cache miss. allocate memory and load from file.
        void* page = malloc(PAGE_SIZE);
        uint32_t num_pages = pager->file_length / PAGE_SIZE;
        if(pager->file_length % PAGE_SIZE)
        {
            num_pages += 1;
        }
        if(page_num < num_pages)
        {
            lseek(pager->file_descriptor, page_num * PAGE_SIZE, SEEK_SET);
            ssize_t bytes_read = read(pager->file_descriptor, page, PAGE_SIZE);
            if(bytes_read == -1)
            {
                printf("Error reading file!\n");
                exit(EXIT_FAILURE);
            }
        }
        pager->pages[page_num] = page;
        if(page_num >= pager->num_pages)
        {
            pager->num_pages = page_num + 1;
        }
    }
    return pager->pages[page_num];
}

void pager_flush(Pager* pager, uint32_t page_num)
{
    if(pager->pages[page_num] == NULL)
    {
        printf("Tried to flush null page!\n");
        exit(EXIT_FAILURE);
    }
    off_t offset = lseek(pager->file_descriptor, page_num * PAGE_SIZE, SEEK_SET);

    if (offset == -1)
    {
        printf("Error seeking offset: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    ssize_t bytes_written = write(pager->file_descriptor, pager->pages[page_num], PAGE_SIZE);
    if(bytes_written == -1)
    {
        printf("Error writing to file: %d\n", errno);
        exit(EXIT_FAILURE);
    }
}
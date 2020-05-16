#include <stdio.h>
#include <stdlib.h>


// ------ Hardware ------

struct Sector
{
    int byteCount;
    char bytes[512];
};

struct Sector create_sector()
{
    struct Sector temp;
    temp.byteCount = 0;
    return temp;
}


struct HDD
{
    int totalSectors;
    int usedSectors;
    int freeSectors;
    struct Sector* sectors;
};

struct HDD create_HDD(int bytes)
{
    struct HDD temp;
    temp.totalSectors = bytes / 512;
    temp.freeSectors = temp.totalSectors;
    temp.usedSectors = 0;
    temp.sectors = malloc(temp.totalSectors * sizeof(struct Sector));

    //fill the hdd with sectors
    for(int i = 0; i < temp.totalSectors; i++)
    {
        temp.sectors[i] = create_sector();
    }
    return temp;
}



// ------ Software -------

struct Block
{
    int usedSectors;
    // sector base address
    struct Sector* sectors; 
};

struct Block create_block(struct Sector* baseAddressOfSectorGroupOf8)
{
    struct Block temp;
    temp.usedSectors = 0;
    temp.sectors = baseAddressOfSectorGroupOf8;
    return temp;
}


struct File
{
    int startingBlockInFAT;
    int sizeInBytes;
};

struct File create_file()
{
    printf("Enter the size of a file: ");
    struct File theFile;
    scanf("%d", &theFile.sizeInBytes);
    theFile.startingBlockInFAT = -1;
    return theFile;
}


struct Drive
{
    int numberOfBlocks;
    struct Block* blocks; 
    struct File* files;
};

struct Drive format_drive(struct HDD theHDD)
{
    struct Drive temp;
    temp.numberOfBlocks = theHDD.totalSectors/8;
    temp.blocks = malloc(temp.numberOfBlocks * sizeof(struct Block));
    temp.files = malloc(temp.numberOfBlocks * sizeof(struct File));

    int posOfNextBaseSector = 0;
    for(int i = 0; i < temp.numberOfBlocks; i++)
    {
        temp.blocks[i] = create_block(&theHDD.sectors[posOfNextBaseSector]);
        posOfNextBaseSector += 8;
    }
    return temp;
}



// ------ FAT Implementation ------

struct FatEntry
{
    int busy;
    int next;
};

struct FatEntry create_FatEntry(next_block_index)
{
    struct FatEntry new_entry;
    new_entry.next = next_block_index;
    new_entry.busy = 1;
    return new_entry;
}


struct FileAllocationTable
{
    int numberOfBlocks;
    struct FatEntry* file_blocks;
};

struct FileAllocationTable create_FAT(struct Drive theDrive)
{
    struct FileAllocationTable FAT;

    return FAT;
}






int main()
{
    struct HDD theHDD = create_HDD(1 * 1024 * 1024 * 1024);
    struct Drive theDrive = format_drive(theHDD);
    struct File theFile = create_File();
    printf("the size is %d", theFile.sizeInBytes);
    return 0;
}
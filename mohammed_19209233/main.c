#include <stdio.h>
#include <stdlib.h>
#define M_SIZE 100
int index=0;
// Structure for a Song have title & duration
struct song
{
    char song_title[M_SIZE];
    char song_duration[5];
};
// Structure for a Song have title, duration and artist name
struct sng
{
    char song_title[M_SIZE];
    char artist_name[M_SIZE];
    char song_duration[5];
};
// Structure for a Artist have a list of Songs contain song title & duration
struct artist
{
    char artist_name[M_SIZE];
    struct song song_list[M_SIZE];
    int size;
};
// Structure for Time have minute and secound
struct tim
{
    int m;
    int s;
};
// Structure for Occour that which artist occurs in random playlist how many times
struct occur{
    char artist_name[M_SIZE];
    int occ;
};
// Function for read data from file and return list of Artists
struct artist* read(FILE *fptr)
{
    char str1[M_SIZE];
    struct artist *artists = malloc(sizeof(struct artist) * M_SIZE);
    while (fgets(str1, M_SIZE, fptr) != NULL)
    {
        int s_index=0;
        for(int i=0; i<M_SIZE; i++)         // Save name of Artist
        {
            if(str1[i]!='\n')
                artists[index].artist_name[i] = str1[i];
        }
        // Get song titles and duration until blank line not occurs
        while(1>0)
        {
            fgets(str1, M_SIZE, fptr);
            int s=0, e=0;
            for(int i=0;i<M_SIZE;i++)
            {
                if (str1[i]=='*')
                {
                    s=i-1;
                    break;
                }
            }
            for(int i=s+1;i<M_SIZE;i++)
            {
                if (str1[i]!='*')
                {
                    e=i;
                    break;
                }
            }
            // Save song title
            for(int i=0; i<=s; i++)
            {
                artists[index].song_list[s_index].song_title[i] = str1[i];
            }
            int si=0;
            // Save song duration
            for(int i=e;i<M_SIZE;i++)
            {
                if(str1[i]!='\n')
                {
                    artists[index].song_list[s_index].song_duration[si]=str1[i];
                    si++;
                }
                else{
                    break;
                }
            }
            if(str1[0]=='\n')
                break;
            s_index++;
        }
        // Set total count of songs of this Artist
        artists[index].size=s_index+1;
        index++;
    }
    fclose(fptr);
    return artists;         // Return list of Artists
}
// Function for taking input from keyboard and return a list of Artists
struct artist* input_user()
{
    struct artist *artists = malloc(sizeof(struct artist) * M_SIZE);
    index=0;
    // Repeating process continously until user quits
    while(1>0)
    {
        int s_index=0;
        char artistname[M_SIZE];
        printf("Enter Artist Name (Enter 'quit' to stop entering information):\n");
        gets(artistname);       // Get Artist name
        if(strcmp(artistname,"quit")==0)
        {
            break;
        }
        else
        {
            for(int i=0; i<M_SIZE; i++)         // Save Artist name
            {
                if(artistname[i]!='\n')
                    artists[index].artist_name[i] = artistname[i];
            }
            while(1>0)
            {
                char songtitle[M_SIZE];
                char songduration[5];
                printf("Enter Song Title (Enter 'quit' to stop entering songs for this Artists):\n");
                gets(songtitle);                // Get Song title
                if(strcmp(songtitle,"quit")==0)
                {
                    break;
                }
                else
                {
                    printf("Enter Song Duration:\n");
                    gets(songduration);         // Get Song duration
                    for(int i=0; i<M_SIZE; i++)         // Save Song title
                    {
                        if(songtitle[i]!='\n')
                            artists[index].song_list[s_index].song_title[i] = songtitle[i];
                    }
                    for(int i=0; i<5; i++)              // Save Song duration
                    {
                        if(songduration[i]!='\n')
                            artists[index].song_list[s_index].song_duration[i] = songduration[i];
                    }
                    s_index++;
                }
            }
            artists[index].size = s_index + 1;          // Set total count of songs of this Artist
            index++;
        }
    }
    return artists;             // Return list of Artists
}
// Function for Print all data
void show(struct artist artists[]){
    for(int i=0; i<index; i++)
    {
        printf("\n%s\n",artists[i].artist_name);
        for(int j=0;j<artists[i].size-1;j++)
        {
            printf("\t%s %s***%s\n","o",artists[i].song_list[j].song_title, artists[i].song_list[j].song_duration);
        }
    }
}
// Function for sort Songs according to Song title
void sort1(struct song song_list[],int s)
{
    for(int i=0;i<s-1;i++)
    {
        int j=i;
        while (j > 0 && strcmp(song_list[j - 1].song_title, song_list[j].song_title) > 0)
        {
            struct song tmp;
            tmp = song_list[j - 1];
            song_list[j - 1] = song_list[j];
            song_list[j] = tmp;
            --j;
        }
    }
}
// Function for sort Artists according to Artist name
void sort(struct artist artists[])
{
    for (int i=0;i<index;i++)
    {
        int j=i;
        while (j > 0 && strcmp(artists[j - 1].artist_name, artists[j].artist_name) > 0)
        {
            struct artist tmp;
            tmp = artists[j - 1];
            artists[j - 1] = artists[j];
            artists[j] = tmp;
            --j;
        }
    }
}
// Function that calls Songs sort (sort1)
void sort2(struct artist artists[])
{
    for(int i=0;i<index;i++)
    {
        sort1(artists[i].song_list, artists[i].size);
    }
}
// Function that takes string type Song duration and converts them to number minutes and seconds
// like '10:15' => (m=10,s=15)
struct tim time_parser(char duration[])
{
    int ind=0;
    int e=0;
    char s[2];
    for(int i=0;i<5;i++)        // Tells us from where we have to separate minute and seconds from string
    {
        if(duration[i]==':')
        {
            ind=i;
        }
        if(duration[i]=='\0')
        {
            e=i;
        }
    }
    char m[ind];
    for(int i=0;i<ind;i++)      // Get minutes from string
    {
        m[i] = duration[i];
    }
    int c=0;
    for(int i=ind+1;i<e;i++)        // Get seconds from string
    {
        s[c] = duration[i];
        c++;
    }
    s[c]='\0';
    int mins = atoi(m);         // Converts them to integer
    int secs = atoi(s);         // Converts them to integer
    struct tim timm;
    timm.m=mins;
    timm.s=secs;
    return timm;                // Return object of 'tim' structure
}
// Function that swaps two objects of 'sng' Structure
void swap (struct sng *a, struct sng *b)
{
    struct sng temp = *a;
    *a = *b;
    *b = temp;
}
// Function that shuffles the list of 'sng' Structure
void radn(struct sng sngs[], int s)
{
    srand (time(NULL));
    // Start from the last element and swap
    // one by one. We don't need to run for
    // the first element that's why i > 0
    for (int i = s - 1; i > 0; i--)
    {
        // Pick a random index from 0 to i
        int j = rand() % (i + 1);
        // Swap arr[i] with the element
        // at random index
        swap(&sngs[i], &sngs[j]);
    }
}
// Function that creates a Random Playlist
void randomm(struct artist artists[])
{
    int siz=1;
    int count=0;
    for(int i=0;i<index;i++)
    {
        siz = siz + artists[i].size-2;
    }
    siz = siz + index-1;            // Get count of total songs given
    struct sng *sngs = malloc(sizeof(struct sng) * siz);
    for(int i=0;i<index;i++)        // Save data from list of 'artist' to the list of 'sngs'
    {
        for (int j=0;j<artists[i].size-1;j++)
        {
            for(int k=0;k<M_SIZE;k++)
            {
                sngs[count].artist_name[k] = artists[i].artist_name[k];
                sngs[count].song_title[k] = artists[i].song_list[j].song_title[k];
            }
            for(int k=0;k<5;k++)
            {
                sngs[count].song_duration[k] = artists[i].song_list[j].song_duration[k];
            }
            count++;
        }
    }
    radn(sngs, siz);            // Apply shuffle on list of 'sngs'
    struct sng *snggs = malloc(sizeof(struct sng) * siz);
    struct tim timm;
    struct tim imm;
    timm.m=0;
    timm.s=0;
    imm.m=0;
    imm.s=0;
    int ind=0,ind1=0;
    struct occur *occor = malloc(sizeof(struct occur) * index);
    for (int i=0;i<index;i++)       // Setting occurance value of all artists in random playlist to 0
    {
        for(int kk=0;kk<M_SIZE;kk++)
        {
            occor[i].artist_name[kk] = artists[i].artist_name[kk];
        }
        occor[i].occ = 0;
    }
    while(ind<siz)          // Repeating process untill we get our playlist
    {
        struct tim t = time_parser(sngs[ind].song_duration);        // Get time of current song
        imm.m = timm.m + t.m;
        if(timm.s + t.s ==60)
        {
            imm.m = imm.m + 1;
            imm.s = 0;
        }
        else if(timm.s + t.s > 60)
        {
            imm.m = imm.m + 1;
            int a = timm.s + t.s;
            imm.s = a - 60;
        }
        else{
            imm.s = timm.s +t.s;
        }
        if(imm.m<60)            // If we put this song in our playlist and total time of playlist does not excedes 60 min
        {
            int in=0;
            int ok=0;
            int sta=0;
            for(int i=0;i<index;i++)
            {
                if(strcmp(sngs[ind].artist_name, occor[i].artist_name)==0)
                {
                    in=i;
                    break;
                }
            }
            if(occor[in].occ<3)                 // If Artist occured less than 3 times
            {
                occor[in].occ = occor[in].occ + 1;
                sta=1;
            }
            else                                // Do not allow to add this song to the playlist
            {
                sta = 0;
            }
            if(sta==1)              // If Artist occured less than 3 times means we have to allow it
            {
                for(int k=0;k<M_SIZE;k++)           // Save Artist name and Song title in Random Playlist
                {
                    snggs[ind1].artist_name[k] = sngs[ind].artist_name[k];
                    snggs[ind1].song_title[k] = sngs[ind].song_title[k];
                }
                for(int k=0;k<5;k++)        // Save Song dutaion in Random Playlist
                {
                    snggs[ind1].song_duration[k] = sngs[ind].song_duration[k];
                }
                // Set total time including this Song's duaration
                timm.m = timm.m + t.m;
                if(timm.s + t.s >=60)
                {
                    timm.m = timm.m + 1;
                    timm.s = 0;
                }
                else{
                    timm.s = timm.s +t.s;
                }
                ind1++;
            }
        }
        ind++;
    }
    // Printing out the created Random Playlist
    printf("%s\n","Randomised playlist");
    for(int i=0;i<ind1;i++)
    {
        printf("%s%s%s%s%s%s\n",snggs[i].artist_name,": \"",snggs[i].song_title,"\" (",snggs[i].song_duration,")");
    }
    printf("\n%s%d%s%d\n","Total duration: ",timm.m,":",timm.s);
}
// Main Function
void main()
{
    struct artist *artists;
    char file[50];
    char file1[50];
    char f;
    int stat=0;
    char default_file[50] = "artistes+songs.txt";
    printf("Is there any input file? (y/n): ");
    f = fgetc(stdin);               // Asking if you want to enter filename
    if(f=='y' || f=='Y')            // If Yes
    {
        printf("Enter file name: ");
        scanf("%s", file);
        getchar();
        FILE *fptr;
        // Open the file of given file name
        if ((fptr = fopen(file,"r")) == NULL){
            printf("Error! opening file\n");
            stat=1;
        }
        if(stat==0)             // There is no error while opening file
        {
            artists = read(fptr);       // Read from file
        }
        else                    // If there is any problem in opening file
        {
            artists = input_user();     // takes input from keyboard
        }
    }
    else if(f=='n' || f=='N')       // If No
    {
        FILE *fptr;
        // open the file by default name ('artistes+songs.txt')
        if ((fptr = fopen(default_file,"r")) == NULL){
            printf("Error! opening file");
            stat=1;
        }
        if(stat==0)             // There is no error while opening file
        {
            artists = read(fptr);       // Read from file
        }
        else                    // If there is any problem in opening file
        {
            artists = input_user();     // takes input from keyboard
        }
    }
    int option;
    sort(artists);              // Apply sort on Artists on Artist name
    sort2(artists);             // Apply sort on Song titles
    l:
    printf("\n1- Show All Sorted Data\n2- Generate Randomized Playlist\nChoose Option: ");      // Print options
    scanf("%d",&option);
    if (option>=1 && option <=2)
    {
        if(option==1)
        {
            printf("Sorted Data:\n");
            show(artists);                      // Prints all sorted data
        }
        else
        {
            randomm(artists);                   // Creates a Random Playlist
        }
    }
    else
    {
        printf("Invalid Option try again.\n");
        goto l;
    }
}


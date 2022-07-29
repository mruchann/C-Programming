#include <stdio.h>
#define WIDTH_INDEX 0
#define HEIGHT_INDEX 1
#define TIME_INDEX 2
#define POSITION_INDEX 3
#define SPEED_INDEX 4
#define INTERVAL_INDEX 5
#define ATTACK_INDEX 6

int main() 
{
    long int lengthOfWall;
    long int numberOfTribes;
    long int Wall[100001]; 
    long int tribesInputs[100][7];
    long int i,j,k,p;
    scanf("%ld", &lengthOfWall);
    scanf("%ld", &numberOfTribes);
    for (i = 0; i <= lengthOfWall ;i++)
    {
        Wall[i] = 1;
    }
    for (i = 0; i < numberOfTribes ;i++)
    {
        for (j = 0; j < 7 ;j++)
        {
            scanf("%ld", &tribesInputs[i][j]);
        } 
    }

    for (i = 0; i < numberOfTribes; i++)
    {
        k = tribesInputs[i][POSITION_INDEX];
        for (j = 0; j < tribesInputs[i][ATTACK_INDEX]; j++)
        {
            for (p = k; p < k + tribesInputs[i][WIDTH_INDEX] ; p++)
            {
                if (p < 0 || p > lengthOfWall)
                {
                    continue;
                }
                if (Wall[p] < tribesInputs[i][HEIGHT_INDEX])
                {
                    Wall[p] = tribesInputs[i][HEIGHT_INDEX];
                }
            }  
            k += (tribesInputs[i][INTERVAL_INDEX] * tribesInputs[i][SPEED_INDEX]);  
        }
    }

    for (i = 0; i < lengthOfWall ;i++)
    {
        printf("%ld ", Wall[i]);
    }
    printf("%ld\n", Wall[lengthOfWall]);
    return 0;
}

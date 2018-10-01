// Kyle Wu
// ID: 4205997
// 9/25/18
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

double massSubtract (int n_size, int printOn, int sampleSize);

int main()
{
    srand(time(0));
    int n_size = -1, printOn = -1, sampleSize = -1, trialSize = -1;
    int i = 0, j = 0, end = 0;
    double timeSpent = 0, totalTimeSpent = 0;

    while (end != 1)
    {
        timeSpent = 0; totalTimeSpent = 0;
        printf("This program is designed to subtract two randomly generated n-digit signed integers.\n");
        printf("Please enter a number between 4 and 1000 representing n, the number of digits.\n");
        scanf("%d", &n_size);

        while (n_size < 4 || n_size > 1000)
        {
            printf("The number selected for n is %d, which is not acceptable. Please enter n again.\n", n_size);
            scanf("%d", &n_size);
        }

        printf("The number of digits selected is %d.\n\n", n_size);

        printf("Type in 1 to display differences or 0 to ignore displays. Note that enabling displays will slow down runtime and should be used for checking math only! \n");
        scanf("%d", &printOn);

        while (printOn != 0 && printOn != 1)
        {
            printf("The number selected was not 0 or 1. Please enter 1 to enable displays or 0 to disable displays.\n");
            scanf("%d", &printOn);
        }

        if (printOn == 0)
            printf("Difference displays have been turned off.\n\n");

        else
            printf("Difference displays have been turned on.\n\n");


        printf("Please enter a number between 1 and 100,000 representing the sample size.\n");
        printf("The sample size dictates how many times the program will create and subtract two numbers.\n");
        scanf("%d", &sampleSize);

        while (sampleSize < 1 || sampleSize > 100000)
        {
            printf("The number entered was not between 1 and 100,000. Please enter a number between 1 and 100,000.\n");
            scanf("%d", &sampleSize);
        }

        printf("A sample size of %d has been selected.\n\n", sampleSize);

        printf("Finally, please select a number between 1 and 100 representing the trial size.\n");
        printf("The trial size dictates how many times the program will run through the sample size to create an average runtime.\n");
        scanf("%d", &trialSize);

        printf("A trial size of %d has been selected.\n\n", trialSize);

        while (trialSize < 1 || trialSize > 100)
        {
            printf("The number entered was not between 1 and 100. Please enter a number between 1 and 100.\n");
            scanf("%d", &sampleSize);
        }

        for (j = 0; j < trialSize; j++)
        {
            timeSpent =  massSubtract(n_size, printOn, sampleSize);
            printf("Trial %d completed. Elapsed time: %lf\n", j + 1, timeSpent);
            totalTimeSpent = totalTimeSpent + timeSpent;
        }
        printf("\n");

        printf("Average time spent over %d trial(s) with n = %d digits and sample size %d: %lfs\n\n", trialSize, n_size, sampleSize, totalTimeSpent/trialSize);

        printf("Type in 1 to end or 0 to start trials again.\n");
        scanf("%d", &end);

        printf("\n");

        while (end != 0 && end != 1)
        {
            printf("You have not entered in 0 or 1; type in 1 to end or 0 to start trials again.\n\n");
            scanf("%d", &end);
        }
    }

    return 0;
}

double massSubtract (int n_size, int printOn, int sampleSize)
{
    int *array = malloc(sizeof(int) * n_size);
    int i = 0, j = 0, k = 0, l = 0;
    int ffirst = 0, fsecond = 0, first = 0, second = 0, neg = 0, place = 0, ignore = 0;
    clock_t t = clock();
    double time_taken = 0;

    for (i = 0; i < sampleSize; i++)
    {
        neg = 0, place = 0, ignore = 1;
        ffirst = rand()%10;
        fsecond = rand()%10;
        memset(array, 0, n_size * sizeof(int));

        // A simple check to make sure that our memset is correctly zero-ing out our
        /*for (k = 0; k < n_size; k++)
            printf("array[%d] = %d\n", k, array[k]);
        */

        // We work from both sides. First we determine the larger of the two numbers. If first exceeds second, the difference is positive.
        // If second exceeds first, the difference is negative.
        // We continue subtracting the two from each other until one is greater than the other, filling up the array from the leftside with zeroes.

        while (ffirst == fsecond)
        {
            if (printOn == 1)
            {
                    printf("The first numbers have matched. (%d time(s))\n", place + 1);
                    printf("first = %d, second = %d, array[%d] = %d\n", ffirst, fsecond, place, 0);
            }
            ffirst = rand()%10;
            fsecond = rand()%10;
            place++;
            if (place >= n_size)
                break;
        }

        if (ffirst > fsecond)
        {
            neg = 0;
            array[place] = ffirst - fsecond;
            place++;
        }

        else
        {
            neg = 1;
            array[place] = fsecond - ffirst;
            place++;

        }

        // We now start working from the small side of the array.
        // If the numbers are even, that spot in the array is zero.
        // If first exceeds second, then that spot is positive.
        // If second exceeds first, then that spot would need to carry over 10.
        // Additionally we add any carry-overs already existing within the array spot.

        for (j = n_size - 1; j >= 0 + place; j--)
        {
            first = rand()%10;
            second = rand()%10;

            if (first + array[j] > second)
            {
                array[j] = first - second + array[j];
            }
            else if (first + array[j] < second)
            {
                array[j] = 10 + first - second + array[j];
                array[j - 1] = array[j - 1] - 1;
            }
            else
            {
                array[j] = 0;
            }
            if (printOn == 1)
            {
                if (neg == 0)
                    printf("first = %d, second = %d, array[%d] = %d\n", first, second, j, array[j]);

                else
                    printf("first = %d, second = %d, array[%d] = %d\n", second, first, j, array[j]);
            }
        }

        if (printOn == 1)
        {
            /*while (place > 1)
            {
                printf("first = %d, second = %d, array[%d] = %d\n", first, fsecond, j, array[j], neg);
                j--;
                place--;
            }
            */
            printf("first = %d, second = %d, array[%d] = %d\n", ffirst, fsecond, j, array[j], neg);

            if (neg == 1)
            {
                printf("-");
            }

            for (l = 0; l < n_size; l++)
            {
                if (ignore == 1 && array[l] == 0)
                    continue;

                else
                {
                    ignore = 0;
                    printf("%d", array[l]);
                }
            }

            printf("\n");
        }
    }
    t = clock() - t;
    time_taken = ((double)t/CLOCKS_PER_SEC);

    free(array);

    return time_taken;
}

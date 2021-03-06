// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    char alleles[2];
    struct person *parents[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    // TODO: Allocate memory for new person
    person *human = malloc(sizeof(person));
    if (human == NULL)
    {
        return NULL;
    }
    // Generation with parent data
    if (generations > 1)
    {
        // TODO: Recursively create blood type histories for parents
        human->parents[0] = create_family(generations - 1);
        human->parents[1] = create_family(generations - 1);
        // TODO: Randomly assign child alleles based on parents

        // These two lines look a bit dense so I'll explain below
        human->alleles[0] = human->parents[0]->alleles[rand() % 2];
        human->alleles[1] = human->parents[1]->alleles[rand() % 2];
        // They do the same thing but assign chars to different indexes
        // human->alleles calls the value within human (as human is a pointer)
        // alleles is an array of chars so in each line we are assigned values to
        // the specified index
        // We want to randomly assign the value from the set of alleles of the person's
        // parents
        // So, we call the alleles of the parent and randomly call on of the chars
        // alleles[0] = parents_alleles[random index]
    }

    // Generation without parent data
    else
    {
        // TODO: Set parent pointers to NULL
        human->parents[0] = NULL;
        human->parents[1] = NULL;
        // TODO: Randomly assign alleles
        char allel_types[4] = {'A', 'B', 'O'};
        human->alleles[0] = allel_types[rand() % 3];
        human->alleles[1] = allel_types[rand() % 3];

    }
    // TODO: Return newly created person
    return human;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // handle base case
    if (p != NULL)
    {
        // Make temp pointers for parent pointers
        person *ftmp = p->parents[0];
        person *mtmp = p->parents[1];
        // Free the memory of the current person
        free(p);
        // Recursively look at each person in the linked list
        free_family(ftmp);
        free_family(mtmp);
        // I'm pretty sure that the if statement will take care of hitting nulls
        // Honestly that was accidental but Bob Ross was there to save the day
    }
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    printf("Generation %i, blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}

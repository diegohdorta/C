#include <stdio.h>
#include <stdlib.h>

static void generate_combination(int team_a, int team_b, int i, char team, int goal_a, int goal_b, char *storage)
{
	if (team != ' ')
		storage[i] = team;

	if ((team_a + team_b) == (goal_a + goal_b)) {
	
		storage[i + 1] = '\0';
		fprintf(stderr, "Output [%s]\n", storage);
		
	}
	else {   
		if (team_a < goal_a)
			generate_combination(team_a + 1, team_b, i + 1, 'A', goal_a, goal_b, storage);

		if (team_b < goal_b)
			generate_combination(team_a, team_b + 1, i + 1, 'B', goal_a, goal_b, storage);
	}
}

int main(int argc, char *argv[]) 
{
	char storage[10];
	
	if (argc < 3 || argc > 3) {
		printf("You must execute: %s A B\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	printf("Solving problem using %s and %s...\n\n", argv[1], argv[2]);

	generate_combination(0, 0, -1, ' ', atoi(argv[1]), atoi(argv[2]), storage);
	
	printf("\nProblem solved with success!\n");	
	
	return EXIT_SUCCESS;
}

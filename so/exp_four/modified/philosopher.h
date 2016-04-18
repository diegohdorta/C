#ifndef _PHILOSOPHER_H_
#define _PHILOSOPHER_H_

#define RED 		"\e[31m"
#define BLUE 		"\e[34m"
#define GREEN 		"\e[32m"
#define YELLOW 		"\e[33m"
#define CYAN		"\e[36m"
#define NORMAL		"\e[0m"

#define MAXIMUM_PHILOSOPHERS		5
#define MAXIMUM_SIZE_NAME		25
#define MAXIMUM_SIZE_MESSAGE		150
#define MICROSECONDS			25

#define SOCRATES			RED "Só sei que nada sei!" NORMAL
#define ARISTOTELES			BLUE "O ignorante afirma, o sábio duvida, o sensato reflete!" NORMAL
#define DESCARTES			GREEN "Penso, logo existo! Ou será que estou com fome?" NORMAL
#define ROUSSEAU			YELLOW "Geralmente, aqueles que sabem pouco falam muito e aqueles que sabem muito falam pouco!" NORMAL
#define NIETZSCHE			CYAN "Não há fatos eternos, como não há verdades absolutas!" NORMAL

char philosophers_names[MAXIMUM_PHILOSOPHERS][MAXIMUM_SIZE_NAME] = {RED "Sócrates" NORMAL, BLUE "Aristóteles" NORMAL, GREEN "Descartes" NORMAL, YELLOW "Rousseau" NORMAL, CYAN "Nietzsche" NORMAL}; 
char philosophers_phrases[MAXIMUM_PHILOSOPHERS][MAXIMUM_SIZE_MESSAGE] = {SOCRATES, ARISTOTELES, DESCARTES, ROUSSEAU, NIETZSCHE}; 

#endif /* _PHILOSOPHER_H_DEFINED_ */

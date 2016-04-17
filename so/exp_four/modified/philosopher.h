#ifndef _PHILOSOPHER_H_
#define _PHILOSOPHER_H_

#define MAXIMUM_SIZE_NAME		20
#define MAXIMUM_SIZE_MESSAGE		100
#define MICROSECONDS			25

#define SOCRATES			"Só sei que nada sei!"
#define ARISTOTELES			"O ignorante afirma, o sábio duvida, o sensato reflete!"
#define DESCARTES			"Penso, logo existo! Ou será que estou com fome?"
#define ROUSSEAU			"Geralmente, aqueles que sabem pouco falam muito e aqueles que sabem muito falam pouco!"
#define NIETZSCHE			"Não há fatos eternos, como não há verdades absolutas!"

char philosophers_names[MAXIMUM][MAXIMUM_SIZE_NAME] = {"Sócrates", "Aristóteles", "Descartes", "Rousseau", "Nietzsche"}; 
char philosophers_phrases[MAXIMUM][MAXIMUM_SIZE_MESSAGE] = {SOCRATES, ARISTOTELES, DESCARTES, ROUSSEAU, NIETZSCHE}; 

#endif /* _PHILOSOPHER_H_DEFINED_ */

##
## Epitech project, tek2.
## Clement-Muth, jonathan-Cohen && Sarah-Keppler
## Plazza
##

## ========================================================================== ##

NAME	=	plazza

## ========================================================================== ##

CC	=	g++

RM	=	rm -f

## ========================================================================== ##

PATH_ROOT		=	./
ROOT			=	main.cpp

## ========================================================================== ##

PATH_COMMON		=	./source/Common/
COMMON			=	Pizza.cpp		\
				MyLib.cpp		\
				Exceptions.cpp

## ========================================================================== ##

PATH_ENCAPSULATION	=	./source/Encapsulation/
ENCAPSULATION		=	Queue.cpp		\
				Stream.cpp		\
				Process.cpp		\
				Thread.cpp		\
				Mutex.cpp		\
				ConditionVariable.cpp	\
				UniqueLock.cpp

## ========================================================================== ##

PATH_KITCHEN		=	./source/Kitchen/
KITCHEN			=	Kitchen.cpp		\
				ThreadPool.cpp		\
				Stock.cpp		\
				Cook.cpp

## ========================================================================== ##

PATH_IPC		=	./source/IPC/
IPC			=	Receiver.cpp		\
				Sender.cpp

## ========================================================================== ##

PATH_RECEPTION		=	./source/Reception/
RECEPTION		=	Reception.cpp		\
				Order.cpp

## ========================================================================== ##

SRCS	=	$(addprefix $(PATH_ROOT), $(ROOT))			\
		$(addprefix $(PATH_COMMON), $(COMMON))			\
		$(addprefix $(PATH_ENCAPSULATION), $(ENCAPSULATION))	\
		$(addprefix $(PATH_KITCHEN), $(KITCHEN))		\
		$(addprefix $(PATH_IPC), $(IPC))			\
		$(addprefix $(PATH_RECEPTION), $(RECEPTION))

OBJ	=	$(SRCS:.cpp=.o)

## ========================================================================== ##

CXXFLAGS =	-W		\
		-Wall		\
		-Werror		\
		-pedantic	\
		-I./include/	\
		-ldl		\
		-lpthread

## --------------------------------------------------------------- ##

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(CXXFLAGS)
	@echo -e "\033[01;38;5;10m================Compiling: Done\033[0;0m"

clean:
	@$(RM) *~ vgcore.* ./include/*~ ./src/*~
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

debug:
	@g++ -o $(NAME) $(SRCS) $(CXXFLAGS) -g
	@echo -e "\033[01;38;5;45m============Valgrind compilation: Done\033[0;0m"

.PHONY: all clean fclean re debug

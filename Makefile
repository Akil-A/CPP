GPP=g++
GPPOPT=-std=c++11

OBJ=oppvarming blackjack

all: $(OBJ)

oppvarming:
	$(GPP) $(GPPOPT) oppvarming.cpp -o $@

blackjack:
	$(GPP) $(GPPOPT) blackjack.cpp -o $@


clean: 
	-$(RM) $(OBJ)

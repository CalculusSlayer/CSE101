#------------------------------------------------------------------------------
#  Nayeel Imtiaz, naimtiaz
#  2022 Spring CSE101 PA8
#  Makefile
#  Makefile for CSE 101 Programming Assignment 8
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 8
#
#  make                     makes WordFrequency
#  make DictionaryClient    makes DictionaryClient
#  make clean               removes all binaries
#  make WordFrequencyCheck  runs WordFrequency under valgrind on Gutenberg.txt
#  make DictionaryCheck     runs DictionaryClient under valgrind
#------------------------------------------------------------------------------

MAIN           = WordFrequency
MAIN2          = Order
ADT            = Dictionary
SOURCE         = $(MAIN).cpp
SOURCE2        = $(MAIN2).cpp
OBJECT         = $(MAIN).o
OBJECT2        = $(MAIN2).o
ADT_TEST       = $(ADT)Test
ADT_SOURCE     = $(ADT).cpp
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(MAIN): $(OBJECT) $(ADT_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT_OBJECT) -g

$(MAIN2): $(OBJECT2) $(ADT_OBJECT)
	$(LINK) $(MAIN2) $(OBJECT2) $(ADT_OBJECT) -g

$(ADT_TEST): $(ADT_TEST).o $(ADT_OBJECT)
	$(LINK) $(ADT_TEST) $(ADT_TEST).o $(ADT_OBJECT) -g

$(OBJECT): $(SOURCE) $(ADT_HEADER)
	$(COMPILE) $(SOURCE) -g

$(OBJECT2): $(SOURCE2) $(ADT_HEADER)
	$(COMPILE) $(SOURCE2) -g

$(ADT_TEST).o: $(ADT_TEST).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_TEST).cpp -g

$(ADT_OBJECT): $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE) -g

clean:
	$(REMOVE) $(MAIN) $(MAIN2) DictionaryTest *.o

$(MAIN)Check: $(MAIN)
	$(MEMCHECK) $(MAIN) GutenBerg.txt

$(ADT)Check: $(ADT_TEST)
	$(MEMCHECK) $(ADT_TEST)
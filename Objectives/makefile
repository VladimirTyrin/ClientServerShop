LIB := ../Libraries/
TEST := ../Testing/
SERV := ../Server/
CLT := ../Client/

FLAGS := -g -pedantic -Wall -Wextra -Werror
LIB_OBJECTIVE := RequestParser.o DateProcessor.o Printer.o Reader.o DataBase.o GeneralMethods.o Coder.o HTMLGenerator.o
BASE_HEADERS := $(LIB)RequestArguments.h $(LIB)Purchase.h $(LIB)MainLib.h $(LIB)DefaultConnection.h

all : tempMain random client server htmlclient

############## Compiling libraries ##############

Coder.o : $(LIB)Coder.h $(LIB)Coder.cpp
	g++ $(LIB)Coder.cpp -c $(FLAGS)

GeneralMethods.o : $(LIB)GeneralMethods.*
	g++ $(LIB)GeneralMethods.cpp -c $(FLAGS)

RequestParser.o : $(LIB)RequestParser.* GeneralMethods.o DateProcessor.o $(BASE_HEADERS)
	g++ $(LIB)RequestParser.cpp -c $(FLAGS)

DateProcessor.o : $(LIB)DateProcessor.* $(LIB)Purchase.h
	g++ $(LIB)DateProcessor.cpp -c $(FLAGS)

Printer.o : $(LIB)Printer.* $(BASE_HEADERS)
	g++ $(LIB)Printer.cpp -c $(FLAGS)
	
Reader.o : $(LIB)Reader.* GeneralMethods.o DateProcessor.o $(LIB)Purchase.h
	g++ $(LIB)Reader.cpp -c $(FLAGS)

DataBase.o : DateProcessor.o $(LIB)DataBase.* Printer.o $(BASE_HEADERS)
	g++ $(LIB)DataBase.cpp -c $(FLAGS)

HTMLGenerator.o : $(BASE_HEADERS) $(LIB)HTMLGenerator.*
	g++ $(LIB)HTMLGenerator.cpp -c $(FLAGS)

############## Compiling test modules ##############

tempMain.o : $(TEST)tempMain.cpp $(LIB)DateProcessor.h $(LIB)DataBase.*
	g++ $(TEST)tempMain.cpp -c $(FLAGS)
	
randomMain.o : $(TEST)randomMain.cpp DateProcessor.o GeneralMethods.o
	g++ $(TEST)randomMain.cpp -c $(FLAGS)
	
tempMain: tempMain.o $(LIB_OBJECTIVE)
	g++ $(LIB_OBJECTIVE) tempMain.o -o tempMain $(FLAGS)
	
random : randomMain.o
	g++ DateProcessor.o GeneralMethods.o randomMain.o -o random $(FLAGS)
	
############## Compiling server #####################

Server.o : $(SERV)Server.* $(BASE_HEADERS)
	g++ $(SERV)Server.cpp -c $(FLAGS)
	
mainServer.o : $(SERV)mainServer.cpp Server.o
	g++ $(SERV)mainServer.cpp -c $(FLAGS)

server : Server.o mainServer.o $(LIB_OBJECTIVE)
	g++ Server.o mainServer.o $(LIB_OBJECTIVE) -o server $(FLAGS)
	
############## Compiling client #####################

Client.o : $(CLT)Client.* $(BASE_HEADERS)
	g++ $(CLT)Client.cpp -c $(FLAGS)
	
mainStandardClient.o : $(CLT)mainStandardClient.cpp Client.o
	g++ $(CLT)mainStandardClient.cpp -c $(FLAGS)
	
mainHTMLClient.o : $(CLT)mainHTMLClient.cpp Client.o
	g++ $(CLT)mainHTMLClient.cpp -c $(FLAGS)
	
client : Client.o mainStandardClient.o $(LIB_OBJECTIVE)
	g++ Client.o mainStandardClient.o $(LIB_OBJECTIVE) -o client $(FLAGS)
	
htmlclient : Client.o mainHTMLClient.o $(LIB_OBJECTIVE)
	g++ Client.o mainHTMLClient.o $(LIB_OBJECTIVE) -o htmlclient $(FLAGS)
	
############## Cleaning #####################

clean :
	@ echo "Cleaning..."
	@ rm *.o -rfv
	@ rm ../*/*~ -rf
	@ rm client htmlclient server random tempMain -rfv
	@ echo "Done"
	

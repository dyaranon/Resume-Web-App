#include "crow_all.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <fstream>
#include <vector>
#include <limits.h>
#include <sstream>
#include <unistd.h>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "Game.hpp"
#include "Board.hpp"
#include "Palindrome.hpp"
#include "json.h"
#include "Warriors.hpp"
#include "Battle.hpp"
#include "GameBoard.hpp"
#include "Piece.hpp"
#include "TicTacToeGame.hpp"
#include "HeapSort.hpp"
#include "MaxSubArray.hpp"
#include "quicksort.hpp"
#include "MST.hpp"

using namespace std;
using namespace crow;


//Global hash of each instance of page
unordered_map<string, Game> hangmanHash;
unordered_map<string, string> palindromeHash;
unordered_map<string, std::vector<Warrior>> warriorsHash;
unordered_map<string, TicTacToeGame> ticTacToeGameHash;
unordered_map<string, int*> heapSortHash;
unordered_map<string, int*> maxSubArrayHash;
unordered_map<string, int*> quickSortHash;
unordered_map<string, Graph> MSThash;


void sendFile(response &res, string fileName, string contentType){
    auto ss = std::ostringstream{};
    std::ifstream file("/usr/src/cppweb1/yaranon/public/" + fileName);
    if(file){
        ss << file.rdbuf();
        res.set_header("Content-Type", contentType);
        res.write(ss.str());
        std::string fileContents = ss.str();
    }
    else{
        char f[256];
        res.code = 404;
        res.write("FILE NOT FOUND!!");
        res.write(getcwd(f, 256));
    }
    res.end();
}

void sendHTML(response &res, string fileName){
    sendFile(res, "templates/" + fileName, "text/html");
}

void sendImage(response &res, string fileName){
    sendFile(res, "images/" + fileName, "image/png");
}

void sendScript(response &res, string fileName){
    sendFile(res, "scripts/" + fileName, "text/javascript");
}

void sendStyle(response &res, string fileName){
    sendFile(res, "styles/" + fileName, "text/css");
}

int main(int argc, char* argv[]){

    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](const request &req, response &res){
        sendHTML(res, "index.html"); //Loads initial HTML page
    });

    CROW_ROUTE(app, "/more.html")([](const request &req, response &res){
        sendHTML(res, "more.html");
    });

    CROW_ROUTE(app, "/csprojects.html")([](const request &req, response &res){
        sendHTML(res, "csprojects.html");
    });

    CROW_ROUTE(app, "/hangman/<string>")([&](const request &req, response &res, string ID){
        chdir("usr/src/cppweb1/yaranon");
        nlohmann::json x;
        std::string letter;
        if(req.url_params.get("theLetter") != nullptr){
            letter = req.url_params.get("theLetter");
        }
        if(letter == "~~~~~"){
            Game game = Game(1);
            hangmanHash.insert({ID, game});
            hangmanHash.at(ID).init();
            x["word"] = hangmanHash.at(ID).getWord();
            x["state"] = hangmanHash.at(ID).board.hangman;
            x["category"] = hangmanHash.at(ID).categoryName;
            x["dashes"] = hangmanHash.at(ID).board.dashes.size();
            x["guesses"] = 6;
            x["message"] = "Enter your guess: ";
        }
        else{
            x = hangmanHash.at(ID).playGame(letter);
        }
        chdir("/");
        res.sendJSON(x);
    });

    CROW_ROUTE(app, "/hangmanGUI/<string>")([&](const request &req, response &res, string ID){
        chdir("usr/src/cppweb1/yaranon");
        nlohmann::json x;
        std::string letter;
        if(req.url_params.get("theLetter") != nullptr){
            letter = req.url_params.get("theLetter");
        }
        if(letter == "~"){
            Game game = Game(1);
            hangmanHash.insert({ID, game});
            hangmanHash.at(ID).init();
            hangmanHash.at(ID).pics = {"0_Hangman.png", "1_Hangman.png", "2_Hangman.png", "3_Hangman.png", "4_Hangman.png", "5_Hangman.png", "6_Hangman.png"};
            x["word"] =  hangmanHash.at(ID).getWord();
            x["pics"] =  hangmanHash.at(ID).pics;
            x["category"] =  hangmanHash.at(ID).categoryName;
            x["dashes"] =  hangmanHash.at(ID).board.dashes.size();
            x["guesses"] =  hangmanHash.at(ID).guesses;
        }
        else{
            x = hangmanHash.at(ID).playGame(letter);
        }
        chdir("/");
        res.sendJSON(x);
    });

    CROW_ROUTE(app, "/palindromes/<string>/<string>")([](const request &req, response &res, string ID, string words){
        chdir("usr/src/cppweb1/yaranon");
        palindromeHash.insert({ID, words});
        nlohmann::json x;
        x = getPalindromes(palindromeHash.at(ID));
        palindromeHash.erase(ID);
        chdir("/");
        res.sendJSON(x);
    });

    CROW_ROUTE(app, "/warriors/<string>")([](const request &req, response &res, string ID){
        chdir("usr/src/cppweb1/yaranon");
        std::vector<Warrior> listOfWarriors;
        std::vector<std::string> print;
        nlohmann::json x;
        auto warriorNames = req.url_params.get_list("list");
        for(const auto &i : warriorNames){
            std::string name = i;
            Warrior w = Warrior(5, 100, name);
            listOfWarriors.push_back(w);
        }
        warriorsHash.insert({ID, listOfWarriors});
        Battle battle;
        print = battle.startFight(warriorsHash.at(ID));
        x["print"] = print;
        warriorsHash.erase(ID);
        chdir("/");
        res.sendJSON(x);
    });

    CROW_ROUTE(app, "/tictactoe/<string>")([](const request &req, response &res, string ID){
        chdir("usr/src/cppweb1/yaranon");
        std::string position;
        int num;
        nlohmann::json x;
        if(req.url_params.get("thePosition") != nullptr){
            position = req.url_params.get("thePosition");
            try{
                num = stoi(position);
            } catch(const std::invalid_argument& e1){
                x["win"] = "Input is invalid, ending program";
                std::cerr << "Invalid arguement, error " << e1.what() << std::endl;
                res.sendJSON(x);
            }
            catch (const std::exception& e2) {
                x["win"] = "Input is invalid, ending program";
                std::cerr << "Undefined error " << e2.what() << std::endl;
                res.sendJSON(x);
            }
        }
        if(num == 2147483646){ //init call
            TicTacToeGame game = TicTacToeGame();
            ticTacToeGameHash.insert({ID, game});
            ticTacToeGameHash.at(ID).init();
            x["gb"] = ticTacToeGameHash.at(ID).gb.boardVect;
            x["turn"] = "X's turn. Enter a number 0 - 8 to place your piece: \r\n";
        }
        else{
            x = ticTacToeGameHash.at(ID).playGame(num);
            if(x["win"] != nullptr){
                ticTacToeGameHash.erase(ID);
            }
        }
        chdir("/");
        res.sendJSON(x);
    });

    CROW_ROUTE(app, "/heapsort/<string>")([](const request &req, response &res, string ID){
        chdir("usr/src/cppweb1/yaranon");
        std::string strnum;
        int num, index = 0;
        nlohmann::json x;
        auto list_nums = req.url_params.get_list("listOfNums");
        int* arr = new int[list_nums.size()];
        for(const auto &i : list_nums){
            strnum = i;
            num = stoi(strnum);
            arr[index] = num;
            index++;
        }
        heapSortHash.insert({ID, arr});
        auto start = std::chrono::high_resolution_clock::now();
        x = heapSort(heapSortHash.at(ID), index);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - start;
        float ms = duration.count() * 1000.0f;
        x["time"] = ms;
        delete[] arr;
        heapSortHash.erase(ID);
        chdir("/");
        res.sendJSON(x);
    });

    CROW_ROUTE(app, "/maxSubArray/<string>")([](const request &req, response &res, string ID){
        chdir("usr/src/cppweb1/yaranon");
        nlohmann::json x;
        std::string strnum;
        int num, index = 0;
        auto list_nums = req.url_params.get_list("listOfNums");
        int* arr = new int[list_nums.size()];
        for(const auto &i : list_nums){
            strnum = i;
            num = stoi(strnum);
            arr[index] = num;
            index++;
        }
        maxSubArrayHash.insert({ID, arr});
        auto start = std::chrono::high_resolution_clock::now();
        x["max"] = maxSubArray(maxSubArrayHash.at(ID), 0, index - 1);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - start;
        float ms = duration.count() * 1000.0f;
        x["time"] = ms;
        delete[] arr;
        maxSubArrayHash.erase(ID);
        chdir("/");
        res.sendJSON(x);
    });

    CROW_ROUTE(app, "/MST/<int>/<int>/<string>/<string>")([](const request &req, response &res, int V, int E, string ID, string data){
        chdir("usr/src/cppweb1/yaranon");
        nlohmann::json x;
        Graph G;
        MSThash.insert({ID, G});
        x = MSThash.at(ID).MST(V, E, data);
        MSThash.erase(ID);
        chdir("/");
        res.sendJSON(x);
    });


    CROW_ROUTE(app, "/styles/<string>")([](const request &req, response &res, string fileName){
        sendStyle(res, fileName); //Deals with any CSS
    });

    CROW_ROUTE(app, "/scripts/<string>")([](const request &req, response &res, string fileName){
        sendScript(res, fileName); //Loads javascript dependencies
    });

    CROW_ROUTE(app, "/images/<string>")([](const request &req, response &res, string fileName){
        sendImage(res, fileName); //Deals with any images we might use
    });

    //Necessary Crow stuff to run server 
    char* port = getenv("PORT");
    uint16_t iPort = static_cast<uint16_t>(port != NULL? stoi(port): 18080);
    //cout << "PORT = " << iPort << '\n';
    app.port(iPort).multithreaded().run();

    return 0;
}

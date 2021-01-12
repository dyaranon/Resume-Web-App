var term;
let V = 0, E = 0, check1 = 0, check2 = 0, check3 = 0, check4 = 0, check5 = 0, check6 = 0, check7 = 0, input = 0, input1 = 0, input2 = 0, input3 = 0, input4 = 0, input5 = 0, count = 0, num_warriors = 0;
let guessedLetters = [], listOfWarriors = [], heapList = [], maxSubList = [], quickList = [];
let MST = "";
var ID;

$(document).ready(function(){
    runTerminal();
    //https://gist.github.com/gordonbrander/2230317
    //Generates random session ID :)
    ID = '_' + Math.random().toString(36).substr(2, 9);
    //console.log(ID);
});

function runHangman(letter){
    $.get("/hangman/" + ID, {"theLetter": letter}, function(response){
        let json = JSON.parse(response);
        if(letter == "~~~~~"){ //init run
            term.write("RUNNING HANGMAN.cpp\r\n");
            guessedLetters = [];
            //console.log(json);
            term.write(json["state"] + "\r\n");
            term.write("Category: " + json["category"] + "\t");
            for(let i = 0; i < json["dashes"]; i++){
                term.write(" _");
            }
            term.write("\r\nGuesses remiaining: "+ json["guesses"] + "\r\n");
            term.write(json["message"]);
        }
        else{
            if(json["err"]){
                term.write(json["err"]);
            }
            else{
                term.write(json["state"] + "\r\n");
                term.write("Category: " + json["category"] + "\t");
                for(let i = 0; i < json.dashes.length; i++){
                    term.write(json.dashes[i] + " ");
                }
                term.write("\r\nGuesses remiaining: "+ json["guesses"] + "\r\n");

                if(json["lettersGuessed"]){ //Incorrect guess
                    guessedLetters.push(json["lettersGuessed"]);
                }
                term.write("Letters Guessed: ");
                for(let i = 0; i < guessedLetters.length; i++){
                    term.write(guessedLetters[i] + " ");
                }
                term.write("\r\n");
            }
            if(json["message"]){
                term.write(json["message"] + "\r\n");
                check1 = 0;
                term.write("\r\n\x1B[1;3;31mdyaranon@DEKTOP-123:\x1B[0m/mnt/e$ ");
            }
            else{
                term.write("\r\nEnter your guess: ");
            }
        }
    });
}

function runPalindrome(curr_line){
    $.get("/palindromes/" + ID + "/" + curr_line, {}, function(response){
        let x = JSON.parse(response);
        for(let i = 0; i < x.words.length; i++){
            term.write(x.words[i] + "\r\n");
        }
        term.write("\r\n\x1B[1;3;31mdyaranon@DEKTOP-123:\x1B[0m/mnt/e$ ");
        check3 = 0;
    });
}

function runWarriorsInit(curr_line){
    if(curr_line <= 1){
        term.write("\r\nNot enough warriors for the game!");
        input = 0;
    }
    else{
        term.write("\r\nEnter name for Warrior " + input + ": ");
    }
}

function runWarriorsInput(curr_line){
    listOfWarriors.push(curr_line);
    if(input < num_warriors){
        input++;
        term.write("\r\nEnter name for Warrior " + input + ": ");
    }
    else{
        runWarriors();
    }
}

function runWarriors(){
    $.get("/warriors/" + ID, {"list":listOfWarriors}, function(response){
        let x = JSON.parse(response);
        for(let i = 0; i < x.print.length; i++){
            term.write(x.print[i]);
        }
        term.write("\r\n\x1B[1;3;31mdyaranon@DEKTOP-123:\x1B[0m/mnt/e$ ");
        check2 = 0;
        input = 0;
        listOfWarriors = [];
    });
}

function runTicTacToe(curr_line){
    $.get("/tictactoe/" + ID, {"thePosition": curr_line}, function(response){
        let x = JSON.parse(response);
        if(x["gb"]){
            for(let i = 0; i <= 2; i++){
                for(let j = 0; j <= 4; j++){
                    term.write(x.gb[i][j]);
                }
                term.write("\r\n");
            }
        }
        if(x["turn"]){
            term.write(x["turn"]);
        }
        if(x["message"]){
            term.write(x["message"]);
        }
        if(x["win"]){
            term.write(x["win"] + "\r\n\x1B[1;3;31mdyaranon@DEKTOP-123:\x1B[0m/mnt/e$ ");
            check4 = 0;
            heapList = [];
        }
    });
}

function runHeapSortInput(curr_line){
    if(isNaN(curr_line) || parseInt(curr_line) > 2100000000 || parseInt(curr_line) < -2100000000){
        term.write("\r\nInvalid input, terminating program");
        check5 = 0;
        heapList = [];
    }
    else{
        if(input1 == 0){
            input1 = curr_line;
        }
        else{
            heapList.push(curr_line);
            if(heapList.length == input1){
                runHeapSort();
            }
        }
    }
}

function runHeapSort(){
    $.get("/heapsort/" + ID, {"listOfNums": heapList}, function (response){
        let x = JSON.parse(response);
        term.write(x["sort"] + ";");
        term.write("\r\nOperation took: " + x["time"] + " ms\r\n\x1B[1;3;31mdyaranon@DEKTOP-123:\x1B[0m/mnt/e$ " );
        check5 = 0;
        heapList = [];
    });
}

function runMaxSubArrayInput(curr_line){
    if(isNaN(curr_line) || parseInt(curr_line) > 2100000000 || parseInt(curr_line) < -2100000000){
        term.write("\r\nInvalid input, terminating program");
        check6 = 0;
        maxSubList = [];
    }
    else{
        if(input2 == 0){
            input2 = curr_line;
        }
        else{
            maxSubList.push(curr_line);
            if(maxSubList.length == input2){
                runMaxSubArray();
            }
        }
    }
}

function runMaxSubArray(){
    $.get("/maxSubArray/" + ID, {"listOfNums": maxSubList}, function (response){
        let x = JSON.parse(response);
        term.write("\r\n" + x["max"]);
        term.write("\r\nOperation took: " + x["time"] + " ms\r\n\x1B[1;3;31mdyaranon@DEKTOP-123:\x1B[0m/mnt/e$ " );
        check6 = 0;
        maxSubList = [];
    });
}

function runMSTInput(curr_line){
    if(input4 == 0){
        V = curr_line;
        input4 = 1;
        input5 = 1;
    }
    else if(input5 == 1){
        E = curr_line;
        input5 = 0;
    }
    else{
        MST += curr_line.split(',') + ',';
        count++;
        if(count == E){
            runMST();
        }
    }
}

function runMST(){
    $.get("/MST/" + V + "/" + E + "/" + ID + "/" + MST,{}, function(response){
        let x = JSON.parse(response);
        for(let i = 1; i < x.ans.length; ++i){
            term.write(x.ans[i] + "\r\n");
        }
        term.write("\r\n\x1B[1;3;31mdyaranon@DEKTOP-123:\x1B[0m/mnt/e$ " );
        check7 = 0;
    });
}

function checkInput(curr_line){
    if(check1 == 1){
        runHangman(curr_line)
    }
    else if(check2 == 1){
        if(input == 0){
            if(isNaN(curr_line) || parseInt(curr_line) > 2100000000){
                term.write("\r\nInvalid input, terminating program\r\n\x1B[1;3;31mdyaranon@DEKTOP-123:\x1B[0m/mnt/e$ ");
                check2 = 0;
                input = 0;
                listOfWarriors = [];
            }
            else{
                num_warriors = curr_line;
                input = 1;
                runWarriorsInit(curr_line);
            }
        }
        else{
            runWarriorsInput(curr_line);
        }
    }
    else if(check3 == 1){
        runPalindrome(curr_line);
    }
    else if(check4 == 1){
        runTicTacToe(curr_line);
    }
    else if(check5 == 1){
        runHeapSortInput(curr_line);
    }
    else if(check6 == 1){
        runMaxSubArrayInput(curr_line);
    }
    else if(check7 == 1){
        runMSTInput(curr_line);
    }
    else if(curr_line == 'HANGMAN' || curr_line == 'hangman'){
        check1 = 1;
        runHangman("~~~~~");
    }
    else if(curr_line == 'WARRIORS' || curr_line == 'warriors'){
        check2 = 1;
        listOfWarriors = [];
        term.write("\r\nRUNNING WARRIORS.cpp\r\nEach warrior will have a base damage of 5 and a base health of 100.\r\nAt the beginning of each game, bonus health will be granted ranging from 0 - 10 (random, so some players might start off with more health).\r\nEach turn the warriors will be granted bonus damage ranging from 0 - 9\r\n(also random).The game ends when all but one warrior has 0 health remaining\r\n\r\nEnter number of warriors: ");
    }
    else if(curr_line == "PALINDOME" || curr_line == "PALINDOME FINDER" || curr_line == "palindrome" || curr_line == "palindrome finder"){
        check3 = 1;
        term.write("\r\nENTER A LIST OF WORDS SEPARATED BY A COMMA AND ENDING WITH THE WORD end; I WILL RETURN THE ONES WHICH ARE PALINDROMES AS WELL AS THE ONES\r\nWHICH ARE STILL VALID WORDS WHEN SPELLED BACKWARDS.\r\n(ALTERNATIVELY, DRAG A .TXT FILE)");
    }
    else if(curr_line == "TICTACTOE" || curr_line == "TIC TAC TOE" || curr_line == "tic tac toe" || curr_line == "TIC TAC TOE" || curr_line == "tic tac toe"){
        check4 = 1;
        term.write("\r\nRUNNING TICTACTOE.cpp");
        runTicTacToe("2147483646");
    }
    else if(curr_line == "HEAP SORT" || curr_line == "heap sort"){
        check5 = 1;
        heapList = [];
        term.write("\r\nRUNNING HEAP SORT\r\n");
        term.write("Enter an integer number representing the number of elements to be sorted. Then, input the elements one at a time.");
    }
    else if(curr_line == "MAX SUB ARRAY" || curr_line == "max sub array"){
        check6 = 1;
        maxSubList = [];
        term.write("\r\nRUNNING MAX SUB ARRAY\r\n");
        term.write("Enter an integer number representing the number of elements in the array. Then, input the elements one at a time.");
    }
    else if(curr_line == "MINIMUM SPANNING TREE"){
        check7 = 1;
        term.write("\r\nRUNNING MINIMUM SPANNING TREE\r\n");
        term.write("First, enter the number of vertices |V|, followed by the number of edges |E|.\r\nThen, enter 3 integers separated by a comma where the first number is\r\nvertex u, the second number is vertex v, and the third number is the weight\r\nbetween the two w(u,v). The vertices are numbered 0, 1,..., |V|-1.\r\nDo this |E| times to form a weighted undirected graph...");
    }
    else{
        check1 = 0;
        check2 = 0;
        check3 = 0;
        check4 = 0;
        check5 = 0;
        check6 = 0;
        check7 = 0;
        listOfWarriors = [];
        guessedLetters = [];
        heapList = [];
        maxSubList = [];
        quickList = [];
        MST = [];
        input = 0;
        input1 = 0;
        input2 = 0;
        input3 = 0;
        input4 = 0;
        input5 = 0;
        term.write("\r\nbash: " + curr_line + " command not found \r\n");
    }
}

function runTerminal(){
    term = new Terminal({
        cursorBlink: "block"
    });
    term.open(document.getElementById('terminal'));
    term.write('WELCOME! ' +
        'I HAVE MOST OF MY PROJECTS (which are on my GitHub written in C++)\r\nREADY TO RUN IN THIS TERMINAL! ' +
        'Type one of the following commands and I can run it ' +
        'for you!: (PRESS THE UP ARROW KEY!) (ctrl+c to end a program) \n');
    term.write("\r- HANGMAN");
    term.write("\r\n- WARRIORS");
    term.write("\r\n- TICTACTOE");
    term.write("\r\n- HEAP SORT");
    term.write("\r\n- MAX SUB ARRAY");
    term.write("\r\n- PALINDROME FINDER");
    term.write("\r\n- MINIMUM SPANNING TREE");
    term.write("\r\n\x1B[1;3;31mdyaranon@DEKTOP-123:\x1B[0m/mnt/e$ ");
    
    let curr_line = '';
    let pressed;
    let bCount = 0, line = 0;
    let cmds = ['HANGMAN', 'WARRIORS', 'TIC TAC TOE', 'HEAP SORT','MAX SUB ARRAY','PALINDOME', 'MINIMUM SPANNING TREE'];
    term.on('key', function(key, ev) {
        const printable = !ev.altKey && !ev.altGraphKey && !ev.ctrlKey && !ev.metaKey;
        if(bCount < 0){
            bCount = 0;
        }
        if(ev.keyCode === 38){ //Up arrow key
            if(line == cmds.length){
                line = 0;
            }
            if(pressed){
                let len = curr_line.length;
                while(len > 0){
                    curr_line = curr_line.slice(0, curr_line.length -1);
                    term.write('\b \b');
                    len--;
                }
            }
            curr_line = cmds[line];
            term.write(curr_line);
            line++;
            pressed = true;
        } /*else if(ev.keyCode === 40){ //Down arrow key
            if(line == 0){
                line = cmds.length;
            }
            if(pressed){
                let len = curr_line.length;
                while(len > 0){
                    curr_line = curr_line.slice(0, curr_line.length -1);
                    term.write('\b \b');
                    len--;
                }
            }
            curr_line = cmds[line];
            term.write(curr_line);
            line--;
            pressed = true;
        } */else if (ev.keyCode === 13) { //enter
            checkInput(curr_line);
            curr_line = '';
            bCount = 0;
            term.write('\r\n');
            if(check1 == 0 && check2 == 0 && check3 == 0 && check4 == 0 && check5 == 0 && check6 == 0 && check7 == 0){
                term.write('\x1B[1;3;31mdyaranon@DEKTOP-123:\x1B[0m/mnt/e$ ');
            }
        } else if(ev.keyCode == 67 && ev.ctrlKey){ //ctrl+c
            curr_line = '';
            check1 = 0;
            check2 = 0;
            check3 = 0;
            check4 = 0;
            check5 = 0;
            check6 = 0;
            check7 = 0;
            listOfWarriors = [];
            guessedLetters = [];
            heapList = [];
            maxSubList = [];
            quickList = [];
            MST = [];
            input = 0;
            input1 = 0;
            input2 = 0;
            input3 = 0;
            input4 = 0;
            input5 = 0;
            bCount = 0;
            term.write('\r\n');
            term.write('\x1B[1;3;31mdyaranon@DEKTOP-123:\x1B[0m/mnt/e$ ');
        }else if (ev.keyCode === 8) { //backspace
            bCount--;
            if(bCount >= 0){
                curr_line = curr_line.slice(0, curr_line.length -1);
                term.write('\b \b');
            }     
        } else if (ev.keyCode != '38' && ev.keyCode != '40' && ev.keyCode != '39' && ev.keyCode != '37' && printable) {
            curr_line += ev.key;
            bCount++;
            //console.log(curr_line, ev.key)
            term.write(key);
            line = 0;
        }
    });
    term.on('paste', function(data) {
        term.write(data);
    });
}

function dropHandler(ev){
    //console.log('File(s) dropped');
  
    // Prevent default behavior (Prevent file from being opened)
    ev.preventDefault();
  
    if (ev.dataTransfer.files) {
        let files = ev.dataTransfer.files;
        let data = "";
        file = files[0];
        if(file.type.indexOf("text") == 0){
            let reader = new FileReader();
            reader.onload = function(ev){
                let count = 0;
                data = ev.target.result;
                const words = data.split('\n').flatMap(line => line.split(/\s+/).filter(word => word === word.split('').reverse().join('')));
                term.write("List of words valid when spelt backwards: ");
                for(let i = 0; i < words.length; i++){
                    term.write(words[i]+'\r\n');
                    count++;
                }
                term.write("Number of palindromes: " + count + "\r\n");
                term.write('\x1B[1;3;31mdyaranon@DEKTOP-123:\x1B[0m/mnt/e$ ');
            }
            reader.readAsText(file);
        }
    }

}

function dragOverHandler(ev) {
  ev.preventDefault();
  ev.stopPropagation();
  ev.dataTransfer.dropEffect = 'copy';
}




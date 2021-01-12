var term;
let check = 0;
let guessedLettersGUI = [];
let img = 0;
var ID;

function clickLetter(letter){
    $.get("/hangmanGUI/" + ID, {"theLetter": letter}, function(response){
		let jsonGUI = JSON.parse(response);
		if(letter == "~"){
			guessedLettersGUI = [];
			lg = "";
			img = 0;
			let dashes = "";
			document.getElementById("lettersGuessed").innerHTML = "LETTERS GUSSED: ";
			document.getElementById("displayMessage").innerHTML = "";
			document.getElementById('category').innerHTML = "CATEGORY: " + jsonGUI["category"];
			document.getElementById("pictureArea").innerHTML = ' <img style="width: 144px; height: 290px;" 	src="../images/' + img.toString() + '_Hangman.png">'
        	for(let i = 0; i < jsonGUI["dashes"]; i++){
        	   dashes += "_ ";
        	}
        	document.getElementById('dashes').innerHTML = dashes;
        	document.getElementById('guesses').innerHTML = "GUESSES REMIANING: " + jsonGUI["guesses"];
		}
		else{
			let lg = "";
			let HTMLdashes = "";
        	if(jsonGUI["message"]){
        	    document.getElementById("displayMessage").innerHTML = jsonGUI["message"];
				check = 0;
				makeButtonsOpaque();
			}
			else{
				if(jsonGUI["lettersGuessed"]){ //Incorrect guess
					guessedLettersGUI.push(jsonGUI["lettersGuessed"]);
					img++;
					document.getElementById("pictureArea").innerHTML = ' <img style="width: 144px; height: 290px;" src="../images/' + img.toString() + '_Hangman.png">'
				}
				for(let i = 0; i < guessedLettersGUI.length; i++){
					lg += guessedLettersGUI[i];
					lg += " ";
				}
				for(let i = 0; i < jsonGUI.dashes.length; i++){
        	        HTMLdashes += (jsonGUI.dashes[i] + " ");
				}

			}
			document.getElementById("lettersGuessed").innerHTML = "LETTERS GUSSED: " + lg;
			document.getElementById("guesses").innerHTML = "GUESSES REMAINING: " + jsonGUI["guesses"];
			document.getElementById('dashes').innerHTML = HTMLdashes;
		}
    });
}

function clickStartGame(){
	resetButtons();
	clickLetter("~");
}


$(document).ready(function(){
	makeButtonsOpaque();
	//https://gist.github.com/gordonbrander/2230317
    //Generates random session ID :)
    ID = '_' + Math.random().toString(36).substr(2, 9);
    console.log(ID);
});

function makeButtonsOpaque(){
	document.getElementById('A').disabled = true;
	document.getElementById('A').style.opacity='0.5';
	document.getElementById('B').disabled = true;
	document.getElementById('B').style.opacity='0.5';
	document.getElementById('C').disabled = true;
	document.getElementById('C').style.opacity='0.5';
	document.getElementById('D').disabled = true;
	document.getElementById('D').style.opacity='0.5';
	document.getElementById('E').disabled = true;
	document.getElementById('E').style.opacity='0.5';
	document.getElementById('F').disabled = true;
	document.getElementById('F').style.opacity='0.5';
	document.getElementById('G').disabled = true;
	document.getElementById('G').style.opacity='0.5';
	document.getElementById('H').disabled = true;
	document.getElementById('H').style.opacity='0.5';
	document.getElementById('I').disabled = true;
	document.getElementById('I').style.opacity='0.5';
	document.getElementById('J').disabled = true;
	document.getElementById('J').style.opacity='0.5';
	document.getElementById('K').disabled = true;
	document.getElementById('K').style.opacity='0.5';
	document.getElementById('L').disabled = true;
	document.getElementById('L').style.opacity='0.5';
	document.getElementById('M').disabled = true;
	document.getElementById('M').style.opacity='0.5';
	document.getElementById('N').disabled = true;
	document.getElementById('N').style.opacity='0.5';
	document.getElementById('O').disabled = true;
	document.getElementById('O').style.opacity='0.5';
	document.getElementById('P').disabled = true;
	document.getElementById('P').style.opacity='0.5';
	document.getElementById('Q').disabled = true;
	document.getElementById('Q').style.opacity='0.5';
	document.getElementById('R').disabled = true;
	document.getElementById('R').style.opacity='0.5';
	document.getElementById('S').disabled = true;
	document.getElementById('S').style.opacity='0.5';
	document.getElementById('T').disabled = true;
	document.getElementById('T').style.opacity='0.5';
	document.getElementById('U').disabled = true;
	document.getElementById('U').style.opacity='0.5';
	document.getElementById('V').disabled = true;
	document.getElementById('V').style.opacity='0.5';
	document.getElementById('W').disabled = true;
	document.getElementById('W').style.opacity='0.5';
	document.getElementById('X').disabled = true;
	document.getElementById('X').style.opacity='0.5';
	document.getElementById('Y').disabled = true;
	document.getElementById('Y').style.opacity='0.5';
	document.getElementById('Z').disabled = true;
	document.getElementById('Z').style.opacity='0.5';
}

function resetButtons(){
	document.getElementById('A').disabled = false;
	document.getElementById('A').style.opacity='1';
	document.getElementById('B').disabled = false;
	document.getElementById('B').style.opacity='1';
	document.getElementById('C').disabled = false;
	document.getElementById('C').style.opacity='1';
	document.getElementById('D').disabled = false;
	document.getElementById('D').style.opacity='1';
	document.getElementById('E').disabled = false;
	document.getElementById('E').style.opacity='1';
	document.getElementById('F').disabled = false;
	document.getElementById('F').style.opacity='1';
	document.getElementById('G').disabled = false;
	document.getElementById('G').style.opacity='1';
	document.getElementById('H').disabled = false;
	document.getElementById('H').style.opacity='1';
	document.getElementById('I').disabled = false;
	document.getElementById('I').style.opacity='1';
	document.getElementById('J').disabled = false;
	document.getElementById('J').style.opacity='1';
	document.getElementById('K').disabled = false;
	document.getElementById('K').style.opacity='1';
	document.getElementById('L').disabled = false;
	document.getElementById('L').style.opacity='1';
	document.getElementById('M').disabled = false;
	document.getElementById('M').style.opacity='1';
	document.getElementById('N').disabled = false;
	document.getElementById('N').style.opacity='1';
	document.getElementById('O').disabled = false;
	document.getElementById('O').style.opacity='1';
	document.getElementById('P').disabled = false;
	document.getElementById('P').style.opacity='1';
	document.getElementById('Q').disabled = false;
	document.getElementById('Q').style.opacity='1';
	document.getElementById('R').disabled = false;
	document.getElementById('R').style.opacity='1';
	document.getElementById('S').disabled = false;
	document.getElementById('S').style.opacity='1';
	document.getElementById('T').disabled = false;
	document.getElementById('T').style.opacity='1';
	document.getElementById('U').disabled = false;
	document.getElementById('U').style.opacity='1';
	document.getElementById('V').disabled = false;
	document.getElementById('V').style.opacity='1';
	document.getElementById('W').disabled = false;
	document.getElementById('W').style.opacity='1';
	document.getElementById('X').disabled = false;
	document.getElementById('X').style.opacity='1';
	document.getElementById('Y').disabled = false;
	document.getElementById('Y').style.opacity='1';
	document.getElementById('Z').disabled = false;
	document.getElementById('Z').style.opacity='1';
}

            
// CodeMirror, copyright (c) by Marijn Haverbeke and others
// Distributed under an MIT license: https://codemirror.net/LICENSE

//mIRC mode by Ford_Lawnmower :: Based on Velocity mode by Steve O'Hara

(function(mod) {
  if (typeof exports == "object" && typeof module == "object") // CommonJS
    mod(require("../../lib/codemirror"));
  else if (typeof define == "function" && define.amd) // AMD
    define(["../../lib/codemirror"], mod);
  else // Plain browser env
    mod(CodeMirror);
})(function(CodeMirror) {
"use strict";

CodeMirror.defineMIME("text/mirc", "mirc");
CodeMirror.defineMode("mirc", function() {
  function parseWords(str) {
    var obj = {}, words = str.split(" ");
    for (var i = 0; i < words.length; ++i) obj[words[i]] = true;
    return obj;
  }
  var specials = parseWords("$! $$ $& $? $+ $abook $abs $active $activecid " +
                            "$activewid $address $addtok $agent $agentname $agentstat $agentver " +
                            "$alias $and $anick $ansi2mirc $aop $appactive $appstate $asc $asctime " +
                            "$asin $atan $avoice $away $awaymsg $awaytime $banmask $base $bfind " +
                            "$binoff $biton $bnick $bvar $bytes $calc $cb $cd $ceil $chan $chanmodes " +
                            "$chantypes $chat $chr $cid $clevel $click $cmdbox $cmdline $cnick $color " +
                            "$com $comcall $comchan $comerr $compact $compress $comval $cos $count " +
                            "$cr $crc $creq $crlf $ctime $ctimer $ctrlenter $date $day $daylight " +
                            "$dbuh $dbuw $dccignore $dccport $dde $ddename $debug $decode $decompress " +
                            "$deltok $devent $dialog $did $didreg $didtok $didwm $disk $dlevel $dll " +
                            "$dllcall $dname $dns $duration $ebeeps $editbox $emailaddr $encode $error " +
                            "$eval $event $exist $feof $ferr $fgetc $file $filename $filtered $finddir " +
                            "$finddirn $findfile
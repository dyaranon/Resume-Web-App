function initEditors(){
    loadTextEditor1();
    loadTextEditor2();
    loadTextEditor3();
    loadTextEditor4();
    loadTextEditor5();
    loadTextEditor6();
    loadTextEditor7();
}

function loadTextEditor1(){
    var e1 = CodeMirror.fromTextArea(document.getElementById('editor1'), {
        lineNumbers : true,
        mode: "xml",
        theme: "gruvbox-dark",
        scrollbarStyle: null
    });
}

    
function loadTextEditor2(){
    var e2 = CodeMirror.fromTextArea(document.getElementById('editor2'),{
        lineNumbers : true,
        mode: "javascript",
        theme: "gruvbox-dark",
        scrollbarStyle: null
    });
}

function loadTextEditor3(){
    var e3 = CodeMirror.fromTextArea(document.getElementById('editor3'),{
        lineNumbers : true,
        mode: "clike",
        theme: "gruvbox-dark",
        scrollbarStyle: null
    });
}

function loadTextEditor4(){
    var e3 = CodeMirror.fromTextArea(document.getElementById('editor4'),{
        lineNumbers : true,
        mode: "clike",
        theme: "gruvbox-dark",
        scrollbarStyle: null
    });
}

function loadTextEditor5(){
    var e3 = CodeMirror.fromTextArea(document.getElementById('editor5'),{
        lineNumbers : true,
        mode: "clike",
        theme: "gruvbox-dark",
        scrollbarStyle: null
    });
}

function loadTextEditor6(){
    var e3 = CodeMirror.fromTextArea(document.getElementById('editor6'),{
        lineNumbers : true,
        mode: "clike",
        theme: "gruvbox-dark",
        scrollbarStyle: null
    });
}

function loadTextEditor7(){
    var e3 = CodeMirror.fromTextArea(document.getElementById('editor7'),{
        lineNumbers : true,
        mode: "clike",
        theme: "gruvbox-dark",
        scrollbarStyle: null
    });
}

$(document).ready(function(){
    initEditors();
});
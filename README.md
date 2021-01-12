# Resume_WebApp
A SMALL SITE I MADE WHILE LEARNING HTML, CSS, JAVASCRIPT, and JQUERY. USES C++ BACKEND (CROW)

CAN BE FOUND AT davidyaranon.app

Steps to run on localhost:8080
1. Make sure Docker is installed!
2. cd website/cppweb1/cppbox1
3. docker build -t cppbox1 .
4. cd .. (go back into cppweb1)
5. docker run -v /local/cloned/folder/website/cppweb1:/usr/src/cppweb1 -ti cppbox1:latest bash
6. cd usr/src/cppweb1/yaranon/build
7. make
8. exit
9. docker run -v /local/cloned/folder/website/cppweb1:/usr/src/cppweb1 -p 8080:8080 -e PORT=8080 cppbox1:latest /usr/src/cppweb1/yaranon/build/yaranon
10. open localhost:8080 in browser



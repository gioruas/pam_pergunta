# pam_pergunta

git clone https://github.com/gioruas/pam_pergunta.git

cd pam_pergunta

gcc -fPIC -fno-stack-protector -c pam_questions.c
gcc -shared -o pam_questions.so pam_questions.o

sudo cp pam_questions.so /lib/security/

Adicionando no início de /etc/pam.d/login, após "auth include system-local-login": "auth required pam_questions.so"
sudo chmod 644 /lib/security/pam_questions.so


///////////////////////////////////////////////////////


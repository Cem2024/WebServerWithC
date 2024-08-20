#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1000
#define RESPONSE_SIZE 500

#define GET_REQUEST 50
#define PUT_REQUEST 51
#define DELETE_REQUEST 52

#define OTHER_REQUEST 501



#define BAD_REQUEST 400
#define NOT_FOUND_REQUEST 404


#define FALSE 0
#define TRUE 1


typedef struct s_directory {

    char *name;
    struct s_directory* parent;
    char *data;
    int isDelete;

    struct s_directory* d_one;
    struct s_directory* d_two;
    struct s_directory* d_three;
    struct s_directory* d_four;
    struct s_directory* d_five;
} dir;

dir* createRootDir(char* directory_name){

    dir* new_directory = malloc(sizeof(dir));
    if(new_directory == NULL){
        fprintf(stderr, "error: allocation for filepath not successful.\n");

        return new_directory;
    }

    char* name = malloc((strlen(directory_name) + 1) * sizeof(char));
    if(name == NULL){
        fprintf(stderr, "error: allocation for filepath not successful.\n");

        return new_directory;
    }

    strcpy(name, directory_name);

    new_directory->name = name;
    new_directory->parent = NULL;

    new_directory->data = NULL;
    new_directory->isDelete = FALSE;

    new_directory->d_one = NULL;
    new_directory->d_two = NULL;
    new_directory->d_three = NULL;
    new_directory->d_four = NULL;
    new_directory->d_five = NULL;

    return new_directory;
}

dir* createDirWithParent(dir *current_dir, char *directory_name){

    dir* new_directory = malloc(sizeof(dir));
    if(new_directory == NULL){
        fprintf(stderr, "error: allocation for filepath not successful.\n");

        return new_directory;
    }

    char* name = malloc((strlen(directory_name) + 1) * sizeof(char));
    if(name == NULL){
        fprintf(stderr, "error: allocation for filepath not successful.\n");

        return new_directory;
    }

    strcpy(name, directory_name);

    new_directory->name = name;
    new_directory->parent = current_dir;

    new_directory->data = NULL;
    new_directory->isDelete = FALSE;

    new_directory->d_one = NULL;
    new_directory->d_two = NULL;
    new_directory->d_three = NULL;
    new_directory->d_four = NULL;
    new_directory->d_five = NULL;

    return new_directory;
}

void putData(dir* directory, char *data){

    char *new_data = malloc(sizeof(char) * (strlen(data) + 1));
    if(new_data == NULL){

        fprintf(stderr, "error: allocate in navigateDir crashed.\n");
    }

    memcpy(new_data, data, strlen(data) + 1);

    directory->data = new_data;
}

//result has to be freed from this method
char *getDataFromRequest(char *buffer){

    char* ptr_ContentLength_start;
    char* ptr_ContentLength_end;

    char* string_number;
    long size_number;
    long content_length;

    char* end_p;

    char* data;

    //Get start of number formatted as string
    ptr_ContentLength_start = strstr(buffer, "Content-Length: ") + 16;

    //Get end of number formatted as string
    ptr_ContentLength_end = strstr(ptr_ContentLength_start, "\r\n");

    size_number = ptr_ContentLength_end - ptr_ContentLength_start;

    //Keep Null pointer in string
    string_number = malloc(sizeof(char) * (size_number + 1));
    if(string_number == NULL){

        //TODO wirte ERROR
    }

    memcpy(string_number, ptr_ContentLength_start, size_number + 1);

    content_length = strtol(string_number, &end_p, 10);

    free(string_number);

    if(content_length != 0){

        end_p = strstr(buffer, "\r\n\r\n");
        end_p = end_p + 4;

        data = malloc(sizeof(char) * (content_length + 1));
        if(data == NULL){

            //TODO
            //implement error
        }

        memcpy(data, end_p, content_length + 1);


        return data;
    }

    return NULL;
}

//does path from root to filepath exist? (filepath should be the complete path from root to dest)
int existPath(dir* root, char* filepath){

    dir* next;

    char *slash = "/";
    char *directories;

    //TODO formatierung
    char *new_fp = malloc(sizeof(char) * (strlen(filepath) + 1));
    if(new_fp == NULL){

        fprintf(stderr, "error: allocate in navigateDir crashed.\n");
    }

    //TODO
    //does strcpy add null terminator?
    memcpy(new_fp, filepath, strlen(filepath) + 1);

    directories = strtok(new_fp, slash);

    while(directories != NULL){

        if(root->d_one != NULL){

            if(strcmp(root->d_one->name, directories) == 0){

                next = root->d_one;

                root = next;
                directories = strtok(NULL, slash);
                continue;
            }
        }
        if(root->d_two != NULL){

            if(strcmp(root->d_two->name, directories) == 0){

                next = root->d_two;
                root = next;
                directories = strtok(NULL, slash);
                continue;
            }

        }
        if(root->d_three != NULL){

            if(strcmp(root->d_three->name, directories) == 0){

                next = root->d_three;
                root = next;
                directories = strtok(NULL, slash);
                continue;
            }

        }
        if(root->d_four != NULL){

            if(strcmp(root->d_four->name, directories) == 0){

                next = root->d_four;
                root = next;
                directories = strtok(NULL, slash);
                continue;
            }

        }
        if(root->d_five != NULL){

            if(strcmp(root->d_five->name, directories) == 0){

                next = root->d_five;
                root = next;
                directories = strtok(NULL, slash);
                continue;
            }

            free(new_fp);
            return FALSE;
        }
        else{

            free(new_fp);
            return FALSE;
        }


    }

    free(new_fp);
    return TRUE;
}

dir* stepDir(dir* current_dir, char* new_dir_path){

    dir* next;

    //trying to find the filepath
    if(current_dir->d_one != NULL ){

        if(strcmp(current_dir->d_one->name, new_dir_path) == 0){

            next = current_dir->d_one;
            return next;
        }
    }
    if(current_dir->d_two != NULL){

        if(strcmp(current_dir->d_two->name, new_dir_path) == 0){

            next = current_dir->d_two;
            return next;
        }

    }
    if(current_dir->d_three != NULL){

        if(strcmp(current_dir->d_three->name, new_dir_path) == 0){

            next = current_dir->d_three;
            return next;
        }

    }
    if(current_dir->d_four != NULL){

        if(strcmp(current_dir->d_four->name, new_dir_path) == 0){

            next = current_dir->d_four;
            return next;
        }

    }
    if(current_dir->d_five != NULL){

        if(strcmp(current_dir->d_five->name, new_dir_path) == 0){

            next = current_dir->d_five;
            return next;
        }
    }

    //Filepath not found, trying to create
    if(current_dir->d_one == NULL){

        dir* new_dir = createDirWithParent(current_dir, new_dir_path);
        current_dir->d_one = new_dir;

        next = current_dir->d_one;
    }
    else if(current_dir->d_two == NULL){

        dir* new_dir = createDirWithParent(current_dir, new_dir_path);
        current_dir->d_two = new_dir;

        next = current_dir->d_two;
    }
    else if(current_dir->d_three == NULL){

        dir* new_dir = createDirWithParent(current_dir, new_dir_path);
        current_dir->d_three = new_dir;

        next = current_dir->d_three;
    }
    else if(current_dir->d_four == NULL){

        dir* new_dir = createDirWithParent(current_dir, new_dir_path);
        current_dir->d_four = new_dir;

        next = current_dir->d_four;
    }
    else if(current_dir->d_five == NULL){

        dir* new_dir = createDirWithParent(current_dir, new_dir_path);
        current_dir->d_five = new_dir;

        next = current_dir->d_five;
    }
        //Filepath is full
    else{

        next = NULL;
    }

    return next;
}

//This method navigate always paths to the "filepath" and creates directories if necessary
//Only returns NULL if filepath is full (one node has to many sub-folders)
dir* navigateDir(dir* root,char *filepath){

    //TODO: verlierern wir root hierdurch?
    dir* current_dir = root;

    char *slash = "/";
    char *directories;

    char *new_fp = malloc(sizeof(char) * (strlen(filepath) + 1));
    if(new_fp == NULL){

        fprintf(stderr, "error: allocate in navigateDir crashed.\n");
    }


    //TODO
    //does strcpy add null terminator?
    memcpy(new_fp, filepath, strlen(filepath) + 1);

    directories = strtok(new_fp, slash);

    while(directories != NULL){

        current_dir = stepDir(current_dir, directories);
        if(current_dir == NULL){

            fprintf(stderr, "error: directory is full [navigate].\n");

            free(new_fp);
            return NULL;
        }


        directories = strtok(NULL, slash);

    }

    free(new_fp);
    return current_dir;
}

//Deletes currentDir and all sub-folders iteratively. Does not delete parents
void deleteAllFiles(dir* current_dir) {

    current_dir->isDelete = TRUE;

    //check if all child directories are empty
    do{

        dir* next = current_dir->d_one;

        current_dir->d_one = NULL;

        if(next == NULL){

            next = current_dir->d_two;
            current_dir->d_two = NULL;

            if(next == NULL){

                next = current_dir->d_three;
                current_dir->d_three = NULL;

                if(next == NULL){

                    next = current_dir->d_four;
                    current_dir->d_four = NULL;

                    if(next == NULL){

                        next = current_dir->d_five;
                        current_dir->d_five = NULL;

                        //if all empty, delete current folder and set next to parent.
                        //except is it the original folder, then set next to NULL and delete current folder
                        if(next == NULL){

                            if(current_dir->isDelete == FALSE){

                                next = current_dir->parent;
                            }
                            else{

                                next = NULL;
                                current_dir ->isDelete = FALSE;

                                if(current_dir->parent != NULL){

                                    if(current_dir->parent->d_one == current_dir){

                                        current_dir->parent->d_one = NULL;
                                    }
                                    else if(current_dir->parent->d_two == current_dir){

                                        current_dir->parent->d_two = NULL;
                                    }
                                    else if(current_dir->parent->d_three == current_dir){

                                        current_dir->parent->d_three = NULL;
                                    }
                                    else if(current_dir->parent->d_four == current_dir){

                                        current_dir->parent->d_four = NULL;
                                    }
                                    else if(current_dir->parent->d_five == current_dir){

                                        current_dir->parent->d_five = NULL;
                                    }
                                }
                            }

                            //free current directory
                            if(current_dir->data != NULL){

                                free(current_dir->data);
                            }

                            free(current_dir->name);
                            free(current_dir);
                        }
                    }
                }
            }
        }

        current_dir = next;
    }
    while(current_dir != NULL);

}

long getPort(char *argv1){

    char *end_p;
    long port_number = strtol(argv1, &end_p, 10);

    //check if given number is a port
    if (port_number <= 0 || *end_p != '\0') {

        fprintf(stderr, "error: input is not a port!\n");
        exit(1);

    } else {

        return port_number;
    }
}

int checkSyntaxHeader(char *first_row){

    int error_code = BAD_REQUEST;
    char *space = " ";

    char *temp = malloc(sizeof(char) * (strlen(first_row) + 1));
    if(temp == NULL){

        fprintf(stderr, "error: could not allocate memory in syntax check.\n");
        exit(1);
    }

    //TODO
    // NULL terminator?
    strcpy(temp, first_row);

    char *sub_string = strtok(temp, space);
    if(sub_string == NULL){

        free(temp);
        return BAD_REQUEST;
    }


    if(strcmp(sub_string, "GET") == 0){

        error_code = GET_REQUEST;
    }
    else if(strcmp(sub_string, "PUT") == 0){

        error_code = PUT_REQUEST;
    }
    else if(strcmp(sub_string, "DELETE") == 0){

        error_code = DELETE_REQUEST;
    }
    else if(strcmp(sub_string, "HEAD") == 0 || strcmp(sub_string, "POST") == 0 || strcmp(sub_string, "CONNECT") == 0
            || strcmp(sub_string, "OPTIONS") == 0 ||strcmp(sub_string, "TRACE") == 0){

        error_code = OTHER_REQUEST;
    }
    else{

        free(temp);
        return BAD_REQUEST;
    }

    sub_string = strtok(NULL, space);
    if(sub_string == NULL){

        free(temp);
        return BAD_REQUEST;
    }

    sub_string = strtok(NULL, space);
    if(sub_string == NULL){

        free(temp);
        return BAD_REQUEST;
    }

    if(strstr(sub_string, "HTTP/1.1\r\n") == NULL && strstr(sub_string, "HTTP/1.0\r\n") == NULL){

        free(temp);
        return BAD_REQUEST;
    }

    free(temp);

    return error_code;
}

char *getString(char* start, long size){

    char *newString = malloc((size) * sizeof(char));
    if(newString == NULL){

        fprintf(stderr, "error: could allocate memory for new string.\n");
        exit(1);
    }

    memcpy(newString, start, size);

    return newString;
}

size_t send_message(int client, int methode_code, int flag, dir* root, char* filepath, char* data){

    char reply_BAD[] = "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n";
    char reply_NOT_FOUND[] = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
    char reply_FORBIDDEN[] = "HTTP/1.1 403 Forbidden\r\nContent-Length: 0\r\n\r\n";
    char reply_OTHER[] = "HTTP/1.1 501 Not Implemented\r\nContent-Length: 0\r\n\r\n";
    char* reply_OK;
    char* reply_CREATED;

    dir* current_dir;



    switch (methode_code) { // NOLINT(hicpp-multiway-paths-covered)

        case OTHER_REQUEST:
            if(send(client, reply_OTHER, strlen(reply_OTHER),0) == -1){

                return -1;
            }
            break;

        case BAD_REQUEST:
            if(send(client, reply_BAD, strlen(reply_BAD),0) == -1){

                return -1;
            }
            break;

        case GET_REQUEST:

            if(existPath(root, filepath) == FALSE){

                if(send(client, reply_NOT_FOUND, strlen(reply_NOT_FOUND),0) == -1){

                    return -1;
                }
            }
            else{

                current_dir = navigateDir(root, filepath);

                char reply_tmp[RESPONSE_SIZE];
                sprintf(reply_tmp,  "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\n\r\n%s", strlen(current_dir->data), current_dir->data);

                reply_OK = malloc(sizeof(char) * strlen(reply_tmp));
                if(reply_OK == NULL){

                    fprintf(stderr, "error: allocate in send_message crashed.\n");

                    return -1;
                }

                memcpy(reply_OK, reply_tmp, strlen(reply_tmp));

                if(send(client, reply_OK, strlen(reply_OK),0) == -1){

                    free(reply_OK);
                    return -1;
                }

                free(reply_OK);
            }
            break;

        case PUT_REQUEST:

            if(existPath(root, filepath) == FALSE){

                current_dir = navigateDir(root, filepath);

                if(data != NULL){

                    putData(current_dir, data);
                }


                char reply_tmp[RESPONSE_SIZE];
                sprintf(reply_tmp,  "HTTP/1.1 201 Created\r\nContent-Length: 0\r\n\r\n");

                reply_CREATED = malloc(sizeof(char) * strlen(reply_tmp));
                if(reply_CREATED == NULL){

                    fprintf(stderr, "error: allocate in send_message crashed.\n");

                    return -1;
                }

                memcpy(reply_CREATED, reply_tmp, strlen(reply_tmp));

                if(send(client, reply_CREATED, strlen(reply_CREATED),0) == -1){

                    free(reply_CREATED);
                    return -1;
                }
            }
            else{

                current_dir = navigateDir(root, filepath);

                char reply_tmp[RESPONSE_SIZE];
                sprintf(reply_tmp,  "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n");

                reply_CREATED = malloc(sizeof(char) * strlen(reply_tmp));
                if(reply_CREATED == NULL){

                    fprintf(stderr, "error: allocate in send_message crashed.\n");

                    return -1;
                }

                memcpy(reply_CREATED, reply_tmp, strlen(reply_tmp));

                if(send(client, reply_CREATED, strlen(reply_CREATED),0) == -1){

                    free(reply_CREATED);
                    return -1;
                }

                free(reply_CREATED);
            }

            break;

        case DELETE_REQUEST:

            if(existPath(root, filepath) == FALSE){

                if(send(client, reply_NOT_FOUND, strlen(reply_NOT_FOUND),0) == -1){

                    return -1;
                }
            }
            else{

                current_dir = navigateDir(root, filepath);

                deleteAllFiles(current_dir);

                char reply_tmp[RESPONSE_SIZE];
                sprintf(reply_tmp,  "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n");

                reply_OK = malloc(sizeof(char) * strlen(reply_tmp));
                if(reply_OK == NULL){

                    fprintf(stderr, "error: allocate in send_message crashed.\n");

                    return -1;
                }

                memcpy(reply_OK, reply_tmp, strlen(reply_tmp));

                if(send(client, reply_OK, strlen(reply_OK),0) == -1){

                    free(reply_OK);
                    return -1;
                }

                free(reply_OK);

            }
            break;

    }

    return 0;
}



void startWebserver(int client_socket, int server_socket, unsigned short server_port, int *c_bool, int *s_bool, dir* root){

    // variables used for socket initialization
    unsigned long port = server_port;
    struct sockaddr_in socket_addr;

    // variables used for request handling
    long recv_size;
    unsigned long left_size = 0;



    char buffer[BUFFER_SIZE] = "";


    // socket()
    printf("creating socket\n");
    if((server_socket = socket(AF_INET, SOCK_STREAM,0)) < 0){

        fprintf(stderr, "error: socket could not be created!\n");
        return;
    }
    //set for error handling in main function
    *s_bool = TRUE;

    socket_addr.sin_family = AF_INET;
    socket_addr.sin_port = htons(port);
    socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // bind()
    printf("binding socket\n");
    if(bind(server_socket, (struct sockaddr *) &socket_addr, sizeof(socket_addr)) == -1){

        fprintf(stderr, "error: socket could not be bound!\n");
        return;
    }

    // listen()
    printf("listening for connection.\n");

    if(listen(server_socket,10) != 0){

        fprintf(stderr, "error: something went wrong, while listening for a connection.\n");

        return;
    }

    while(TRUE){

        // resetting recv_size, so we do not run into an endless inner loop
        recv_size = 1;

        char *ptr_message;

        // accept()
        printf("accepting connection.\n");
        if((client_socket = accept(server_socket, NULL, NULL)) == -1){

            fprintf(stderr, "error: something went wrong, while accepting a connection.\n");

            return;
        }
        //set for error handling in main function
        *c_bool = TRUE;

        while(recv_size != 0){

            // recv()
            printf("receiving data.\n");
            if((recv_size = recv(client_socket,&(buffer[left_size]) ,sizeof(buffer) - left_size,0)) == -1){

                fprintf(stderr, "error: something went wrong, while receiving data.\n");

                return;
            }

            // calculating how many bytes are currently in our array
            left_size = recv_size + left_size;

            // send()
            printf("sending data.\n");
            while(left_size != 0){

                ptr_message = strstr(buffer, "\r\n\r\n");
                if(ptr_message == NULL){

                    break;
                }

                char *ptr_header = strstr(buffer, "\r\n") + 2;

                char *first_row = getString(&buffer[0], ptr_header - &buffer[0]);

                int method_code;
                method_code = checkSyntaxHeader(first_row);

                char *URI = NULL;

                char *ptr_uri_start;
                char *ptr_uri_end;

                char *data;

                if(method_code != BAD_REQUEST && method_code != OTHER_REQUEST){

                    ptr_uri_start = strstr(first_row, " ") + 2;
                    ptr_uri_end = strstr(ptr_uri_start, " ");

                    URI = getString(ptr_uri_start, ptr_uri_end - ptr_uri_start);
                }


                free(first_row);

                data = getDataFromRequest(buffer);


                // replying to the first request in our buffer
                if(send_message(client_socket, method_code, 0, root, URI, data) == -1){

                    fprintf(stderr, "error: something went wrong, while sending the data.\n");

                    return;
                }

                free(data);
                free(URI);

                // get start of new message
                // Attention!!! I chose the buffer 1000+ so we do not get out of bounds but still possible with enough data
                ptr_message = (ptr_message + 4);

                // removing the first Request in the buffer
                left_size = left_size - (ptr_message - &buffer[0]);

                char temp_buffer[BUFFER_SIZE] = "";

                memmove(temp_buffer, ptr_message, &buffer[sizeof(buffer) - 1] - ptr_message);
                memset(buffer, 0, sizeof(buffer));
                memcpy(buffer, temp_buffer, sizeof(buffer));
            }
        }
    }
}

int main(int argc, char** argv) {

    /*
    char filepath1[] = "static/tmp";
    char filepath2[] = "static/usr/Desktop";
    char filepath3[] = "static/usr/Documents";

    char deletePath[] = "static/usr";


    char root_name[] = "root";
    dir* root_dir;
    dir* current_dir;

    root_dir = createRootDir(root_name);

    deleteAllFiles(root_dir);

     */
    unsigned long port;
    int s, c = 0;
    int s_bool, c_bool = FALSE;

    // error: too many arguments

    if(argc != 2 ){

        fprintf(stderr, "error: too many or too few arguments!\n");
        exit(1);
    }
        // using user specified port and error handling
    else{

        port = getPort(argv[1]);
    }
    //create client and socket in Main so that we always need to close them!!!!


    dir* root = createRootDir("root");

    dir* current_dir = navigateDir(root, "static/foo");
    putData(current_dir, "Foo");

    current_dir = navigateDir(root, "static/bar");
    putData(current_dir, "Bar");

    current_dir = navigateDir(root, "static/baz");
    putData(current_dir, "Baz");

    // run webserver until stopped
    startWebserver(c,s,port, &c_bool, &s_bool,root);

    //close all sockets and free up memory if server crashes
    if(c_bool == TRUE){

        close(c);
        close(s);
    }
    else if(s_bool == TRUE){

        close(s);
    }

    free(root);

    // exit program with an error
    exit(1);

    return 0;
}

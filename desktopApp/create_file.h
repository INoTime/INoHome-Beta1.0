void create() {
    struct stat stats0, stats1;

    stat("files/tmp", &stats0);
    if (!S_ISDIR(stats0.st_mode)) {
        mkdir("files/tmp", 0777);
    }
    stat("files/crypt", &stats1); 
    if (!S_ISDIR(stats1.st_mode)) {
        mkdir("files/crypt", 0777);
    }
}
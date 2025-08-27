#define MAX_URLS 10000
#define BASE_URL "http://tinyurl.com/"

char* urlStore[MAX_URLS];
int urlCount = 0;

char* encode(char* longUrl) {
    urlStore[urlCount] = strdup(longUrl);
    int id = urlCount;
    urlCount++;

    char* shortUrl = (char*)malloc(100);
    sprintf(shortUrl, "%s%d", BASE_URL, id);
    return shortUrl;
}

char* decode(char* shortUrl) {
    int id = atoi(shortUrl + strlen(BASE_URL));
    if (id >= 0 && id < urlCount) {
        return urlStore[id];
    }
    return "";
}
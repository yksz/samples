#include <cstdio>
#include <map>
#include <string>

#define NEW_ERROR(err) newError(err, __FILE__, __LINE__)

enum class error : uint8_t {
    success = 0,
    unknown_error,
};

static std::string errorFile;
static int errorLine;

static error newError(const error& err, const char* file, int line) {
    errorFile = file;
    errorLine = line;
    return err;
}

static std::string getErrorFile() {
    return errorFile;
}

static int getErrorLine() {
    return errorLine;
}

static const std::map<error, const char*> errorMessages {
    { error::success, "Success" },
    { error::unknown_error, "Unknown error" }
};

const char* getErrorMessage(const error& err) {
    auto it = errorMessages.find(err);
    return it != errorMessages.end() ? it->second : "Message not found";
}

error calc(int x, int y, int& result) {
    return NEW_ERROR(error::unknown_error);
}

int main(void) {
    int result;
    error err = calc(10, 20, result);
    if (err != error::success) {
        printf("%s:%d: %s\n",
                getErrorFile().c_str(), getErrorLine(), getErrorMessage(err));
    } else {
        printf("No error\n");
    }
    return 0;
}

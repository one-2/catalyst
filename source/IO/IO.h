#ifndef IO.h
#define IO.h

class IO
{
    IO(std::string out_path);
    tensor load_from_csv(std::string path);
    model load_checkpoint(std::string path);
    int write_checkpoint(std::string label);
    std::ostream& operator<<;
}

#endif // IO_H

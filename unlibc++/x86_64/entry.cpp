int main(int argc, char* argv[]);

extern "C" int cpp_entry(int argc, char* argv[]) {
    return main(argc, argv);
}

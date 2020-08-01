#ifndef control_bindings_H
#define control_bindings_H

class Control_bindings {

    private:

        // properties
        // commands
        const char* up;
        const char* left;
        const char* down;
        const char* right;

    public:
    
        // constructor
        Control_bindings(const char* up, const char* left,
                            const char* down, const char* right);
        
        // SDL keycode to code command
        const char * SDLToCommand (const char * keycode);
        
        // deconstructor    
        ~Control_bindings();

};

#endif
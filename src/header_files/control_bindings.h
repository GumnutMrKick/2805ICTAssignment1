#ifndef control_bindings_H
#define control_bindings_H

class Control_bindings {

    private:

        // properties
        // commands
        int up, right, down, left;

    public:
    
        // constructor
        Control_bindings (const int up, const int left,
                            const int down, const int right);
        
        // SDL keycode to code command
        int SDLToCommand (const int keycode);
        
        // deconstructor    
        ~Control_bindings ();

};

#endif
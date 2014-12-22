Program created by sroccaserra (cf. https://sourceforge.net/users/sroccaserra/) - december 2005.


   The OpenGL Obj Loader - v0.2.4


1. Release

This is the second iteration, no speed or memory optimisation has been done.
The largest model I tried (350,000 triangles) loaded alright on a 700 Mhz Mac, and Tool generated its normals without a sweat. Slightly choppy framerate though.


2. Build

TooL uses Boost, OpenGL, SDL, and SDL_image libraries.

Note: TooL uses CppUnit for unit testing. Define a TOOL_UNIT_TESTING macro (with -D) to enable unit testing.
If you don't want to use (or still don't have) CppUnit, just remove the "Test" directory from the build.

   2.1 Mac OS X

   - Install Boost and both the SDL and SDL_image developer package.
   - Open the XCode project provided with the source.
   - Remove the "Test" directory from the project if you are so inclined (cf. above).
   - Build the main target...

   2.2 Windows/Unix

   - Install Boost and both the SDL and SDL_image developer package.
   - Create a C++ command line project with your favourite compiler.
   - Add all the source files except the "Mac OS X" directory (leave "Test" as well if you are so inclined).
   - Register external include files & libraries (OpenGL, SDL...).
   - Prefix header: TooL uses a precompiled prefix header ("stable.pch"). Be sure to enable and set the prefix header if your compiler has this ability.  Otherwise you'll have to add it manually at the begining of every .cpp file.
   - Change "OpenGL/glu.h" to "GL/glu.h" in the prefix header ("stable.pch").
   - Build...


3. Usage

Mac OS X:
Drag a .obj file on the application icon, or
> open Tool.app [file.obj]

Linux:
> ./Tool [file.obj]

Windows:
C:/ Tool.exe [file.obj]

If no file is specified, Tool opens "Data/Cube.obj" (provided with the source).
If the mesh has no normals, flat normals are generated.
If the file is larger than 1 Mo, a progression percentage is displayed while parsing.
- Dragging with the left mouse button rotates the model.
- Dragging with the left mouse button and Ctrl translates the model.
- Dragging with the left mouse button and Alt translates the camera.
- Dragging with the left mouse button and Alt translates the camera.
- Enter resets the view.
- Q, or ESC to quit.


4. Tests

Tested on Mac OS X.
Feedback from other platform users is largely welcome.


5. License

This program is licensed under the GNU General Public License.
You can find a copy of the GNU General Public License in this package (GPL.txt), or alternatively here:
http://www.gnu.org/licenses/gpl.txt.


6. References

http://www.boost.org/
http://www.opengl.org/
http://libsdl.org/
http://sourceforge.net/projects/cppunit

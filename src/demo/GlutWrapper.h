#include <glload/gl_3_0.h>
#include <glload/gll.hpp>
#include <GL/freeglut.h>
#include <nbody/System.h>

#include <cstdint>
#include <string>
#include <iostream>
#include <stdexcept>

typedef class nbody::System System;

class Shaders;

class GlutWrapper {
  static void displayCallback();
  static void reshapeCallback( int theWidth, int theHeight );
  static void keyboardCallback( unsigned char key, int x, int y );
  static void mouseCallback( int button, int state, int x, int y );
	static void openglDebug( GLenum source, GLenum type, GLuint id, 
													 GLenum severity, GLsizei length,
													 const GLchar* message, GLvoid* userParam );
	Shaders *_shaders;
	void initVertexBuffers( size_t bufSize, float *buf );
protected:
  int _width, _height;
  int _windowId;
  std::string _windowTitle;
	size_t _bufSize;
	float *_buf; 
	GLuint _positionBufferObject;
	GLuint _vao;
	GLuint _program;



	

  static GlutWrapper *_instance;
  GlutWrapper( const GlutWrapper& ) = delete;
  GlutWrapper& operator=( const GlutWrapper& ) = delete;
public:
	enum Mode { DEBUG, NDEBUG };
  Mode _debugMode;
  // Pointer to Simulation
  System *_sys;


  GlutWrapper();
  GlutWrapper( Mode debugMode );
	GlutWrapper( const std::string &title );
	GlutWrapper( const std::string &title, 
               Mode debugMode = Mode::NDEBUG );
  
  //New Constructor to be used
  GlutWrapper( const std::string &title,
	       System *sys,
	       Mode debugMode = Mode::NDEBUG);

    virtual ~GlutWrapper();

  void init( int argc, char **argv, int theWidth, int theHeight, Shaders *shaders, size_t bufSize = 0, float *buf = nullptr );
  void createWindow();
	void run();
  static GlutWrapper* getInstance();

  inline int width() const { return _width; }
  inline int height() const { return _height; }

  virtual void display() = 0;
  virtual void reshape( int theWidth, int theHeight ) = 0;
  virtual void keyboard( unsigned char key, int x, int y );
  virtual void mouse( int button, int state, int x, int y );
private:

};

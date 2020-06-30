import numpy
from OpenGL.GLUT import *
from OpenGL.GL import *
from OpenGL.GLU import gluBuild2DMipmaps
from PIL import Image

from src.base_settings import BaseSettings


def push_pop(original_function):
    def new_function(*args, **kwargs):
        glPushMatrix()
        original_function(*args, **kwargs)
        glPopMatrix()
        return

    return new_function


class MaterialAndTextures(BaseSettings):
    def __init__(self):
        super().__init__()

    @staticmethod
    def load_texture(filename="../texture.bmp"):
        img = Image.open(filename)
        img_data = numpy.array(list(img.getdata()), numpy.uint8)
        texture = glGenTextures(1)

        glBindTexture(GL_TEXTURE_2D, texture)
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE)
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST)
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)

        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, img.size[0], img.size[1], GL_RGB, GL_UNSIGNED_BYTE, img_data)
        return texture

    @push_pop
    def draw_sphere(self):
        glEnable(GL_BLEND)
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
        glTranslatef(2.0, 0.0, 0.0)  # x , y, z
        glMaterialfv(GL_FRONT, GL_DIFFUSE, (0.0, 0.0, 1.0, 0.5))
        glutSolidSphere(0.8, 16, 16)  # glutWireCube(GLdouble width);
        glDisable(GL_BLEND)

    @push_pop
    def draw_torus(self):
        glMaterialf(GL_FRONT, GL_SHININESS, 128.0)
        glutSolidTorus(0.2, 0.7, 20, 40)  # glutWireTorus(GLdouble dInnerRadius, GLdouble dOuterRadius, GLint nSides, GLint nRings);

    @push_pop
    def draw_cube(self):
        glTranslatef(-2.0, 0.0, 0.0)  # x , y, z
        glBindTexture(GL_TEXTURE_2D, self.load_texture())

        glEnable(GL_TEXTURE_GEN_S)
        glEnable(GL_TEXTURE_GEN_T)
        glEnable(GL_TEXTURE_2D)

        glutSolidCube(1)

        glDisable(GL_TEXTURE_GEN_S)
        glDisable(GL_TEXTURE_GEN_T)
        glDisable(GL_TEXTURE_2D)

    def draw(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glPushMatrix()
        glRotatef(self.xrot * 2, 0.0, 1.0, 0.0)

        self.draw_torus()
        self.draw_cube()
        self.draw_sphere()

        glPopMatrix()
        glutSwapBuffers()


mt = MaterialAndTextures()
mt.run()

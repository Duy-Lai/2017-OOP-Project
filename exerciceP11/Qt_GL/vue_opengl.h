#ifndef VUEOPENGL_H
#define VUEOPENGL_H

#include <QGLShaderProgram>
#include <QMatrix4x4>
#include "vertex_shader.h"
#include "glsphere.h"
#include "SupportADessin.h"
#include "Grain.h"
#include "Obstacle.h"
#include "Systeme.h"

class VueOpenGL : public SupportADessin {
	public:
	virtual void dessine(GrainLJ_1 const&) override;
	virtual void dessine(GrainLJ_2 const&) override;
	virtual void dessine(Dalle const&) override;
	virtual void dessine(Brique const&) override;
    virtual void dessine(Sphere const&) override;
	virtual void dessine(Systeme const&) override;
	void init();
	void initializePosition();
	void setProjection(QMatrix4x4 const& projection)
	{ prog.setUniformValue("projection", projection); }
	void translate(double x, double y, double z);
	void rotate(double angle, double dir_x, double dir_y, double dir_z);
	void dessineAxes(QMatrix4x4 const&, bool = true);
	void dessinePlan(Dalle const&);
	void dessineSphere(QMatrix4x4 const& = QMatrix4x4(), double = 1.0, double = 1.0, double = 1.0);
	private:
	QGLShaderProgram prog;
	GLSphere sphere;
	QMatrix4x4 matrice_vue;
};

#endif

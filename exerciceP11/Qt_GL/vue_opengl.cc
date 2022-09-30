#include "vue_opengl.h"

void VueOpenGL::dessine(GrainLJ_1 const& grain) {
    QMatrix4x4 matrice;
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    matrice.translate(grain.get_p().get_x(),grain.get_p().get_y(),grain.get_p().get_z());
    matrice.scale(grain.get_r());
    dessineSphere(matrice, 1.0, 1.0, 0.35);  // jaune
}

void VueOpenGL::dessine(GrainLJ_2 const& grain) {
    QMatrix4x4 matrice;
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    matrice.translate(grain.get_p().get_x(),grain.get_p().get_y(),grain.get_p().get_z());
    matrice.scale(grain.get_r());
    dessineSphere(matrice, 1.0, 0.6, 0.6);  // rose
}

void VueOpenGL::dessine(Dalle const& plan) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    dessinePlan(plan);
}

void VueOpenGL::dessine(Brique const& brique) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (auto& face : brique.get_f()) {
        dessinePlan(face);
	}
}

void VueOpenGL::dessine(Sphere const& sphere) {
	QMatrix4x4 matrice;
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	matrice.translate(sphere.get_o().get_x(),sphere.get_o().get_y(),sphere.get_o().get_z());
	matrice.scale(sphere.get_r());
    dessineSphere(matrice,0.75,0.0,0.75);  // violet
}

void VueOpenGL::dessine(Systeme const& systeme) {
	QMatrix4x4 matrice;
    matrice.scale(50.0);
    dessineAxes(matrice);
    for (auto& grain : systeme.get_g()) {
        if (grain->get_tg() == LJ1) dessine(GrainLJ_1(*grain));
        if (grain->get_tg() == LJ2) dessine(GrainLJ_2(*grain));
    }
	for (auto& dalle : systeme.get_d()) {
		dessine(*dalle);
	}
	for (auto& brique : systeme.get_b()) {
		dessine(*brique);
	}
	for (auto& sphere : systeme.get_s()) {
		dessine(*sphere);
    }
}

void VueOpenGL::init() {
	prog.addShaderFromSourceFile(QGLShader::Vertex,   ":/vertex_shader.glsl");
	prog.addShaderFromSourceFile(QGLShader::Fragment, ":/fragment_shader.glsl");
	prog.bindAttributeLocation("couleur", CouleurId);
	prog.link();
	prog.bind();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	sphere.initialize();
	initializePosition();
}

void VueOpenGL::initializePosition() {
    matrice_vue.setToIdentity();
    matrice_vue.translate(-40.0, -195.0, -400.0);
	matrice_vue.rotate(225.0, 0.0, 0.0, 1.0);
	matrice_vue.rotate(60.0, 1.0, -1.0, 0.0);
}

void VueOpenGL::translate(double x, double y, double z) {
	QMatrix4x4 translation_supplementaire;
	translation_supplementaire.translate(x, y, z);
	matrice_vue = translation_supplementaire * matrice_vue;
}

void VueOpenGL::rotate(double angle, double dir_x, double dir_y, double dir_z) {
	QMatrix4x4 rotation_supplementaire;
	rotation_supplementaire.rotate(angle, dir_x, dir_y, dir_z);
	matrice_vue = rotation_supplementaire * matrice_vue;
}

void VueOpenGL::dessineAxes (QMatrix4x4 const& point_de_vue, bool en_couleur) {
	prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
	glBegin(GL_LINES);
	// axe X
	if (en_couleur) {
		prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
	} else {
		prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0); // blanc
	}
	prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
	prog.setAttributeValue(SommetId, 1.0, 0.0, 0.0);
	// axe Y
	if (en_couleur) prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); // vert
	prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
	prog.setAttributeValue(SommetId, 0.0, 1.0, 0.0);
	// axe Z
	if (en_couleur) prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); // bleu
	prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
	prog.setAttributeValue(SommetId, 0.0, 0.0, 1.0);
	glEnd();
}

void VueOpenGL::dessinePlan(Dalle const& plan) {
	prog.setUniformValue("vue_modele", matrice_vue);
	glBegin(GL_QUADS);
    prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0);
	prog.setAttributeValue(SommetId, plan.get_o().get_x(), plan.get_o().get_y(), plan.get_o().get_z());
    prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0);
	prog.setAttributeValue(SommetId, (plan.get_o()+plan.get_e_L()*plan.get_lo()).get_x(), (plan.get_o()+plan.get_e_L()*plan.get_lo()).get_y(), (plan.get_o()+plan.get_e_L()*plan.get_lo()).get_z());
    prog.setAttributeValue(CouleurId, 1.0, 1.0, 0.0);
	prog.setAttributeValue(SommetId, (plan.get_o()+plan.get_e_L()*plan.get_lo()+plan.get_e_l()*plan.get_la()).get_x(), (plan.get_o()+plan.get_e_L()*plan.get_lo()+plan.get_e_l()*plan.get_la()).get_y(), (plan.get_o()+plan.get_e_L()*plan.get_lo()+plan.get_e_l()*plan.get_la()).get_z());
    prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0);
	prog.setAttributeValue(SommetId, (plan.get_o()+plan.get_e_l()*plan.get_la()).get_x(), (plan.get_o()+plan.get_e_l()*plan.get_la()).get_y(), (plan.get_o()+plan.get_e_l()*plan.get_la()).get_z());
	glEnd();
}

void VueOpenGL::dessineSphere(QMatrix4x4 const& point_de_vue, double rouge, double vert, double bleu) {
	prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
	prog.setAttributeValue(CouleurId, rouge, vert, bleu);
	sphere.draw(prog, SommetId);
}

#include "MatrixHandler.h"
void MatrixHandler::rotate(glm::mat4x4* tMat, float angle, glm::vec3 axis) {
	*tMat = glm::rotate(*tMat, angle, axis);
}
void MatrixHandler::translate(glm::mat4x4* tMat, glm::vec3 transVec) {
	*tMat= glm::translate(*tMat, transVec);
}
void MatrixHandler::scale(glm::mat4x4* tMat, glm::vec3 scaleVec) {
	*tMat = glm::scale(*tMat, scaleVec);
}
void MatrixHandler::reset(glm::mat4x4* tMat) {
	*tMat = glm::mat4(1.0f);;
}
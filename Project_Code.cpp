    // =====================================
    // Responsive UI Panels (Bottom Aligned)
    // =====================================
    glEnable(GL_BLEND);
    
    float pad = 20.0f;
    float pW = 280.0f; 
    float pH = 180.0f; 
    
    float leftX = -screenW/2.0f + pad;
    float bottomY = -screenH/2.0f + pad;

    glColor4f(0.04f, 0.12f, 0.2f, 0.8f); 
    drawRoundedRect(leftX, bottomY, pW, pH, 5, true); 
    glColor3f(0.3f, 0.6f, 0.8f); glLineWidth(2.0f);
    drawRoundedRect(leftX, bottomY, pW, pH, 5, false);
    
    float textX = leftX + 15.0f;
    float headerY = bottomY + pH - 25.0f;

    glBegin(GL_LINES); glVertex2f(leftX + 10, headerY - 5); glVertex2f(leftX + pW - 10, headerY - 5); glEnd();

    drawText(leftX + 35.0f, headerY, GLUT_BITMAP_HELVETICA_18, "KEYBOARD CONTROLS", 0.5f, 0.8f, 1.0f);
    
    float step = 22.0f;
    drawText(textX, headerY - step*1.2f, GLUT_BITMAP_HELVETICA_12, "Arrows: Translate Rocket", 1.0f, 1.0f, 1.0f);
    drawText(textX, headerY - step*2.2f, GLUT_BITMAP_HELVETICA_12, "A / D: Rotate", 1.0f, 1.0f, 1.0f);
    drawText(textX, headerY - step*3.2f, GLUT_BITMAP_HELVETICA_12, "W / S: Scale (Zoom)", 1.0f, 1.0f, 1.0f);
    drawText(textX, headerY - step*4.2f, GLUT_BITMAP_HELVETICA_12, "Q / E: Shear (Skew)", 1.0f, 1.0f, 1.0f);
    drawText(textX, headerY - step*5.2f, GLUT_BITMAP_HELVETICA_12, "SPACE: Fire Laser", 1.0f, 0.6f, 0.2f);
    drawText(textX, headerY - step*6.2f, GLUT_BITMAP_HELVETICA_12, "ESC: Exit Program", 1.0f, 0.3f, 0.3f);
    float rightX = screenW/2.0f - pW - pad;

    glColor4f(0.04f, 0.12f, 0.1f, 0.8f); 
    drawRoundedRect(rightX, bottomY, pW, pH, 5, true);
    glColor3f(0.2f, 0.5f, 0.3f); glLineWidth(2.0f);
    drawRoundedRect(rightX, bottomY, pW, pH, 5, false); glLineWidth(1.0f);

    float rTextX = rightX + 15.0f;
    glBegin(GL_LINES); glVertex2f(rightX + 10, headerY - 5); glVertex2f(rightX + pW - 10, headerY - 5); glEnd();

    drawText(rightX + 65.0f, headerY, GLUT_BITMAP_HELVETICA_18, "CURRENT STATUS", 0.5f, 1.0f, 0.5f);
    
    std::stringstream p, r, s, sh;
    p << "Position: (" << std::fixed << std::setprecision(2) << posX << ", " << posY << ")";
    r << "Rotation Angle: " << angle << " deg";
    s << "Scale Factor: " << scale << "x";
    sh << "Shear X: " << std::fixed << std::setprecision(2) << shearX;

    drawText(rTextX, headerY - step*1.5f, GLUT_BITMAP_HELVETICA_12, p.str(), 1.0f, 1.0f, 1.0f);
    drawText(rTextX, headerY - step*2.8f, GLUT_BITMAP_HELVETICA_12, r.str(), 1.0f, 1.0f, 1.0f);
    drawText(rTextX, headerY - step*4.1f, GLUT_BITMAP_HELVETICA_12, s.str(), 1.0f, 1.0f, 1.0f);
    drawText(rTextX, headerY - step*5.4f, GLUT_BITMAP_HELVETICA_12, sh.str(), 1.0f, 1.0f, 1.0f);
    
    drawText(rTextX, headerY - step*6.7f, GLUT_BITMAP_HELVETICA_12, "Rendering: ", 1.0f, 1.0f, 1.0f);
    drawText(rTextX + 80.0f, headerY - step*6.7f, GLUT_BITMAP_HELVETICA_12, "Active", 0.4f, 1.0f, 0.4f); 

    glDisable(GL_BLEND);
    }


void drawLasers() {
    for (size_t i = 0; i < lasers.size(); i++) {
        if (lasers[i].active) {
            glPushMatrix();
            glTranslatef(lasers[i].x, lasers[i].y, 0.0f);
            glRotatef(lasers[i].angle, 0.0f, 0.0f, 1.0f);
            glScalef(lasers[i].scale, lasers[i].scale, 1.0f); 
            glColor3f(0.0f, 1.0f, 1.0f); 
            glBegin(GL_QUADS); glVertex2f(-2.0f, 0.0f); glVertex2f(2.0f, 0.0f); glVertex2f(2.0f, 20.0f); glVertex2f(-2.0f, 20.0f); glEnd();
            glPopMatrix();
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBackgroundAndUI();
    drawLasers();
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);        
    glRotatef(angle, 0.0f, 0.0f, 1.0f);    
    glScalef(scale, scale, 1.0f);          
    float shearMatrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, shearX, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
    glMultMatrixf(shearMatrix);
    drawSpaceship();
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    screenW = (float)w;
    screenH = (float)h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-screenW/2.0f, screenW/2.0f, -screenH/2.0f, screenH/2.0f);
    glMatrixMode(GL_MODELVIEW);
}

void handleContinuousMovement() {
    float moveSpeed = 5.0f; 
    if (specialKeys[GLUT_KEY_UP]) posY += moveSpeed;
    if (specialKeys[GLUT_KEY_DOWN]) posY -= moveSpeed;
    if (specialKeys[GLUT_KEY_LEFT]) posX -= moveSpeed;
    if (specialKeys[GLUT_KEY_RIGHT]) posX += moveSpeed;
    if (keys['a'] || keys['A']) angle += 3.0f;
    if (keys['d'] || keys['D']) angle -= 3.0f;
    if (keys['w'] || keys['W']) scale += 0.02f;
    if (keys['s'] || keys['S']) { if (scale > 0.2f) scale -= 0.02f; }
    if (keys['q'] || keys['Q']) shearX -= 0.02f;
    if (keys['e'] || keys['E']) shearX += 0.02f;
    if (keys['r'] || keys['R']) { posX = 0.0f; posY = 0.0f; angle = 0.0f; scale = 1.0f; shearX = 0.0f; lasers.clear(); }
    if (keys[' '] && fireCooldown == 0) {
        float rad = angle * PI / 180.0f;
        float localNoseX = 80.0f * shearX * scale;
        float localNoseY = 80.0f * scale;
        float startX = posX + (localNoseX * cosf(rad) - localNoseY * sinf(rad));
        float startY = posY + (localNoseX * sinf(rad) + localNoseY * cosf(rad));
        float dirX = shearX * cosf(rad) - 1.0f * sinf(rad);
        float dirY = shearX * sinf(rad) + 1.0f * cosf(rad);

bool found = false;
        for (size_t i = 0; i < lasers.size(); i++) {
            if (!lasers[i].active) {
                lasers[i].x = startX; lasers[i].y = startY; 
                lasers[i].dx = dirX * 15.0f; lasers[i].dy = dirY * 15.0f;
                lasers[i].angle = laserAngle; 
                lasers[i].scale = scale; 
                lasers[i].active = true; found = true; break;
            }
        }
        if(!found) lasers.push_back({startX, startY, dirX * 15.0f, dirY * 15.0f, laserAngle, scale, true});
        
        fireCooldown = 5;
    }
}

void timer(int value) {
  if (fireCooldown > 0) fireCooldown--;
    flameTime += 0.5f; handleContinuousMovement();

    for(int i = 0; i < 200; i++) {
        stars[i].y -= stars[i].speed; 
        if(stars[i].y < -screenH/2.0f) { 
            stars[i].y = screenH/2.0f; 
            stars[i].x = (rand() % (int)screenW) - screenW/2.0f; 
        }
        stars[i].brightness = 0.5f + ((rand() % 50) / 100.0f); 
    }
for (size_t i = 0; i < lasers.size(); i++) {
        if (lasers[i].active) {
            lasers[i].x += lasers[i].dx; lasers[i].y += lasers[i].dy; 
            if (lasers[i].y > screenH/2 || lasers[i].y < -screenH/2 || lasers[i].x > screenW/2 || lasers[i].x < -screenW/2) lasers[i].active = false; 
        }
    }
    glutPostRedisplay(); glutTimerFunc(30, timer, 0); 
}

void keyboardDown(unsigned char key, int x, int y) {
    keys[key] = true;
    if (key == 27) exit(0);
}

void keyboardUp(unsigned char key, int x, int y) { keys[key] = false; }
void specialDown(int key, int x, int y) { specialKeys[key] = true; }
void specialUp(int key, int x, int y) { specialKeys[key] = false; }

void init() {
    glClearColor(0.01f, 0.02f, 0.05f, 1.0f); 
    for(int i = 0; i < 200; i++) { 
        stars[i].x = (rand() % 2000) - 1000; 
        stars[i].y = (rand() % 1500) - 750; 
        stars[i].size = (rand() % 3) + 1.0f; 
        stars[i].speed = ((rand() % 5) + 2) * 0.5f; 
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_ALPHA);
    glutInitWindowSize(screenW, screenH); glutCreateWindow("INTERACTIVE SPACESHIP CONTROLLER");
    init(); 
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboardDown); glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialDown); glutSpecialUpFunc(specialUp);
    glutTimerFunc(0, timer, 0); glutMainLoop(); return 0;
}

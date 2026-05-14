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

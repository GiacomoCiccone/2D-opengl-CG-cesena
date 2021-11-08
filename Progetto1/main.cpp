#include "Lib.h"
#include "ShaderMaker.h"

//id of shader program
static unsigned int programId;
const float v = 5.0;

//uniforms
glm::mat4 Projection; //projection matrix
GLuint projMatrixPTR, modelMatrixPTR;

//models
Sky* skyModel;
MountainFG* mountainFGModel, *mountainFGModelOutline;
MountainBG* mountainBGModel;
Cloud* cloudModel;
Ball* ballModel;
Square* squareModel;
Eyes* eyes;
Mouth* mouth;
Star* starModel;

//playerinfo
float playerPosx = 80;
float playerPosy = 40 + 67;
float velX = 0.0;
float velY = 0.0;
bool jumping = false;
bool moveF = false; //moving forward
bool moveB = false; //moving backward
glm::vec4 currentColor = glm::vec4(255, 255, 0, 1.0); //initial color of the ball

//pointer to the offset of the mountainFG (this should be changed)
float* FGOffset;

typedef struct {
    glm::vec2 starPos;
    glm::vec4 starColor;
} starInfo;

//position of the square and the stars
std::vector<glm::vec2> squarePos;
std::vector<starInfo> starsInfo, collectedStars;




/*This function contrain the size of the window at SCR_WIDTH x SCR_HEIGTH*/
void resetSize(int width, int height) {

    glutReshapeWindow(SCR_WIDTH, SCR_HEIGHT);

}

void updateModels() {
    //the ball is jumping
    if (jumping)
    {   
        //if the ball doesn't go under the ground
        if (playerPosy + velY > 40 + 67)
        {   
            //check if is colliding with a star
            for (int i = 0; i < starsInfo.size(); i++)
            {
                //this condition basically check if there is a collision with a star
                if (abs((playerPosx)-(*FGOffset + starsInfo[i].starPos.x)) <= 50 && abs((playerPosy)-(starsInfo[i].starPos.y)) < 50)
                {
                    //if so, ball will become of the color of that star, and we put it in the collected star vector, while removing from the star that should be rendered
                    currentColor = starsInfo[i].starColor;
                    collectedStars.push_back(starsInfo[i]);
                    starsInfo.erase(starsInfo.begin() + i);
                    break;
                }
            }

            //check if colliding with a square
            int ok = -1;
            for (int i = 0; i < squarePos.size(); i += 4)
            {
                if ((playerPosx) >= *FGOffset + squarePos[i].x && (playerPosx) <= *FGOffset + squarePos[i + 3].x + 50 && abs((playerPosy - 40) - (squarePos[i].y + 50)) < 10 && velY < 0 && jumping)
                {
                    ok = i;
                    break;
                }
            }
            //if not update the y position of the ball
            if (ok == -1)
            {
                playerPosy += velY;
                velY -= 1.0;
            }
            //otherwise we are on a square, so the ball bounce
            else {
                playerPosy = squarePos[ok].y + 50 + 40;
                //initial vel is halved to simulate some physics
                velY = abs(velY) * 0.5;
                //when it is too small it should put to 0 otherwise the ball will bounce endlessly
                if (velY < 2)
                {
                    velY = 0;
                    jumping = false;
                }
            }

        }
        //the ball is not jumping
        else {
            //put it on the ground
            playerPosy = 40 + 67;
            //if it was bouncing, apply some physics
            velY = abs(velY) * 0.5;
            //when it is too small it should put to 0 otherwise the ball will bounce endlessly
            if (velY < 1)
            {
                velY = 0;
                jumping = false;
            }

        }
    }

    //ball is moving to the right
    if (moveF)
    {
        //check star collision
        for (int i = 0; i < starsInfo.size(); i++)
        {
            if (abs((playerPosx)-(*FGOffset + starsInfo[i].starPos.x)) <= 50 && abs((playerPosy)-(starsInfo[i].starPos.y)) < 50)
            {
                currentColor = starsInfo[i].starColor;
                collectedStars.push_back(starsInfo[i]);
                starsInfo.erase(starsInfo.begin() + i);
                break;
            }
        }
        //if the ball is not in the middle of the screen
        if (playerPosx + velX < SCR_WIDTH / 2)
        {
            //check square collision
            int ok = -1;
            for (int i = 0; i < squarePos.size(); i += 4)
            {
                if ((playerPosx) >= *FGOffset + squarePos[i].x && (playerPosx) <= *FGOffset + squarePos[i + 3].x + 50)
                {
                    ok = i;
                    break;
                }
            }
            if (ok == -1)
            {
                //acceleration + update position + the ball is not on a square so should fall
                velX < 2.0 ? velX += 0.2 : velX = 2.0;
                playerPosx += 5 * velX;
                jumping = true;
            }
            else {
                //acceleration + update position
                velX < 2.0 ? velX += 0.2 : velX = 2.0;
                playerPosx += 5 * velX;

            }
        }
        //the ball is in the middle of the screen, so we update the background instead of it
        else {
            playerPosx = SCR_WIDTH / 2;
            mouth->updateAngle(-5.0);//rotate ball
            eyes->updateAngle(-5.0); //rotate ball
            starModel->updateOffset(-v * FG_VEL);
            squareModel->updateOffset(-v * FG_VEL);
            mountainFGModel->updateOffset(-v * FG_VEL);
            mountainFGModelOutline->updateOffset(-v * FG_VEL);
            mountainBGModel->updateOffset(-v * BG_VEL);
            cloudModel->updateOffset(-v * CLOUD_VEL);
        }
    }
    //it's not moving backward, decelerate 
    else if (!moveB) {
        velX > 0 ? velX -= 0.5 : velX = 0.0;
        if (playerPosx < SCR_WIDTH / 2)
        {
            playerPosx += velX;
        }
    }

    //same of mooving forward but opposite
    if (moveB)
    {
        for (int i = 0; i < starsInfo.size(); i++)
        {
            if (abs((playerPosx)-(*FGOffset + starsInfo[i].starPos.x)) <= 50 && abs((playerPosy)-(starsInfo[i].starPos.y)) < 50)
            {
                currentColor = starsInfo[i].starColor;
                collectedStars.push_back(starsInfo[i]);
                starsInfo.erase(starsInfo.begin() + i);
                break;
            }
        }
        if (playerPosx + velX > 40)
        {
            int ok = -1;
            for (int i = 0; i < squarePos.size(); i += 4)
            {
                if ((playerPosx) >= squarePos[i].x && (playerPosx) <= squarePos[i + 3].x + 50)
                {
                    ok = i;
                    break;
                }
            }
            if (ok == -1)
            {
                velX < 2.0 ? velX += 0.2 : velX = 2.0;
                playerPosx -= 5 * velX;
                jumping = true;
            }
            else {
                velX < 2.0 ? velX += 0.2 : velX = 2.0;
                playerPosx -= 5 * velX;

            }
        }
        else {
            playerPosx = 40;
            velX = 0;
            mouth->updateAngle(5.0);//rotate ball
            eyes->updateAngle(5.0); //rotate ball
            starModel->updateOffset(v * FG_VEL);
            squareModel->updateOffset(v * FG_VEL);
            mountainFGModel->updateOffset(v * FG_VEL);
            mountainFGModelOutline->updateOffset(v * FG_VEL);
            mountainBGModel->updateOffset(v * BG_VEL);
            cloudModel->updateOffset(v * CLOUD_VEL);
        }
    }
    else if (!moveF) {
        velX > 0 ? velX -= 0.5 : velX = 0.0;
        if (playerPosx < SCR_WIDTH / 2)
        {
            playerPosx -= velX;
        }
    }

}

/*This function implement the display function for the current window, which actually draw object on the screen*/
void drawScene(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUniformMatrix4fv(projMatrixPTR, 1, GL_FALSE, glm::value_ptr(Projection));

    //if 7 stars have been collected
    if (collectedStars.size() == 7)
    {
        // Creating text
        GLTtext* text = gltCreateText();
        gltSetText(text, "Hai vinto!");

        // Begin text drawing (this for instance calls glUseProgram)
        gltBeginDraw();

        // Draw any amount of text between begin and end
        gltColor(1.0f, 1.0f, 1.0f, 1.0f);
        gltDrawText2DAligned(text,
            (GLfloat)(SCR_WIDTH / 2),
            (GLfloat)(SCR_HEIGHT / 6),
            3.0f,
            GLT_CENTER, GLT_CENTER);

        // Finish drawing text
        gltEndDraw();

        // Deleting text
        gltDeleteText(text);
    }
    else {
        updateModels();
    }

    glUseProgram(programId);

    for (int i = 0; i < collectedStars.size(); i++)
    {
        starModel->setColor(collectedStars[i].starColor);
        starModel->buildModel();
        starModel->initVAO();
        starModel->setType(false);
        starModel->setPos(i * 35 + 25, 650);
        starModel->drawModel();
    }

    for (int j = 0; j < 7 - collectedStars.size(); j++) {
        starModel->setColor(glm::vec4(150, 150, 150, 1.0));
        starModel->buildModel();
        starModel->initVAO();
        starModel->setType(false);
        starModel->setPos(j * 35 + 25 + (collectedStars.size() * 35), 650);
        starModel->drawModel();
    }

    ballModel->setColor(currentColor);
    ballModel->buildModel();
    ballModel->initVAO();
    ballModel->setPos(playerPosx, playerPosy);
    ballModel->drawModel();

    for (int i = 0; i < starsInfo.size(); i++)
    {
        starModel->setColor(starsInfo[i].starColor);
        starModel->buildModel();
        starModel->initVAO();
        starModel->setType(true);
        starModel->setPos(starsInfo[i].starPos.x, starsInfo[i].starPos.y);
        starModel->drawModel();
    }

    for (int i = 0; i < squarePos.size(); i++)
    {
        squareModel->setPos(squarePos.at(i).x, squarePos.at(i).y);
        squareModel->drawModel();
    }

    mountainFGModel->drawModel();

    mountainFGModelOutline->drawModel();

    mountainBGModel->drawModel();

    skyModel->drawModel();

    cloudModel->drawModel();
    
    glutSwapBuffers();

}

/*This function init the vertex and fragment shader for the rendering*/
void INIT_SHADER(void) {

    char* vertexShader = (char*)"vertexShader.glsl";
    char* fragmentShader = (char*)"fragmentShader.glsl";

    programId = ShaderMaker::createProgram(vertexShader, fragmentShader);
    glUseProgram(programId);
}

//This function is the callback for keypress event
void keyboardHandler(unsigned char key, int x, int y)  {
    switch (key)
    {
    case 'd':
        moveF = true;
        break;
    case 'a':
        moveB = true;
        break;

    case 32:
        if (velY == 0.0)
        {
            //space pressed
            velY = 15.0;
            jumping = true;
        }
        break;
    }

    glutPostRedisplay();
}

void keyboardHandlerRelease(unsigned char key, int x, int y) {
    switch (key)
    {
    case 'd':
        moveF = false;
        break;
    case 'a':
        moveB = false;
        break;
    }
}

/*This function init the models of the scene*/
void INIT_MODELS() {
    skyModel = new Sky(2);
    skyModel->buildModel();
    skyModel->initVAO();

    mountainFGModel = new MountainFG(150, false);
    mountainFGModel->buildModel();
    mountainFGModel->initVAO();
    FGOffset = mountainFGModel->getOffset();

    mountainFGModelOutline = new MountainFG(150, true);
    mountainFGModelOutline->buildModel();
    mountainFGModelOutline->initVAO();

    mountainBGModel = new MountainBG(150);
    mountainBGModel->buildModel();
    mountainBGModel->initVAO();

    cloudModel = new Cloud(0);
    cloudModel->buildModel();
    cloudModel->initVAO();

    ballModel = new Ball(200);
    ballModel->setColor(currentColor);
    ballModel->buildModel();
    ballModel->initVAO();
    eyes = ballModel->getEyes();
    mouth = ballModel->getMouth();

    squareModel = new Square(4);
    squareModel->buildModel();
    squareModel->initVAO();

    starModel = new Star(10);
    starModel->setColor(glm::vec4(255, 255, 255, 1.0));
    starModel->buildModel();
    starModel->initVAO();


    //put some stars and square in the scene
    for (int i = 1; i <= 50; i++)
    {
        for (int j = 1; j <= 4; j++) {
            //square follow a sin shape
            float a =  4 * abs(sin(i / 4.0));
            squarePos.push_back(glm::vec2(400 * i + j * 52, 40 + 100 * a));
            if ((i % 2) == 0 && j == 2)
            {
                starInfo info;
                info.starPos = glm::vec2(400 * i + j * 52 + 52, 40 + 100 * a + 95);
                i % 6 == 0 ? info.starColor = glm::vec4(255, 0.0, 0.0, 1.0) : i % 4 == 0 ? info.starColor = glm::vec4(0.0, 255, 0.0, 1.0) : info.starColor = glm::vec4(0.0, 0.0, 255, 1.0);
                starsInfo.push_back(info);
            }
        }
    }
}

/*This function get the uniform pointers from the shader programs*/
void getUniforms() {
    Projection = glm::ortho(0.0f, float(SCR_WIDTH), 0.0f, float(SCR_HEIGHT));
    projMatrixPTR = glGetUniformLocation(programId, "Projection");
    modelMatrixPTR = glGetUniformLocation(programId, "Model");
}


int main(int argc, char** argv)
{
    //glut init
    glutInit(&argc, argv);
    glutInitContextVersion(4, 0);
    glutInitContextProfile(GLUT_CORE_PROFILE); //uses core
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //dobule buffered windows, rgba, depth buffer
    glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Progetto 1");

    //callbacks
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resetSize);
    glutKeyboardFunc(keyboardHandler);
    glutKeyboardUpFunc(keyboardHandlerRelease);

    //glew init
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        // Problem: glewInit failed, something is seriously wrong.
        std::cout << "glewInit failed: " << glewGetErrorString(err) << std::endl;
        exit(EXIT_FAILURE);
    }

    // Initialize glText
    gltInit();

    //init programs variables and models
    INIT_SHADER();
    getUniforms();
    INIT_MODELS();

    //init and enable blending calculated ad colorS * alpha + colorD * (1 - alpha)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //starts main loop
    glutMainLoop();

    // Destroy glText
    gltTerminate();

    exit(EXIT_SUCCESS);
}
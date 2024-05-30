#include<C:\Users\Никита\Desktop\КГ ЛР\PSVY_PROEKT\PSVY_PROEKT/glut.h>//Подключениебиблиотекиglut.h
#include <cmath>

// Параметры автомобиля
float carX = 0.0f, carY = 0.0f, carZ = 0.0f;
float carAngle = 0.0f;
float carSpeed = 0.0f; // Изначальная скорость 0
float carTurnSpeed = 2.0f;

float deceleration = 0.05f; // Значение замедления скорости
bool keyStates[256]; // Массив состояний клавиш
// Параметры камеры
float camera_angle_x = 0.0f;
float camera_angle_y = 0.0f;
float camera_distance = 5.0f;
float bridgeLength = 10.0f; // Длина моста
float bridgeWidth = 4.0f;  // Ширина моста
float bridgeHeight = 0.5f; // Высота моста
float rampLength = 5.0f;   // Длина наклонной части
// Координаты моста
float bridgeX = 0.0f; // X координата центра моста
float bridgeY = 2.5f; // Y координата центра моста (высота над землей)
float bridgeZ = 20.0f; // Z координата центра моста
void drawTrees() {
    GLUquadricObj* quadratic;
    quadratic = gluNewQuadric();
    glColor3f(0.0f, 1.0f, 0.0f); // Зеленый цвет для деревьев
    glRotatef(90, -1, 0, 0);
    gluCylinder(quadratic, 0.2f, 0.0f, 2.0f, 32, 32);
    // Освобождаем объект квадрики
    gluDeleteQuadric(quadratic);
}
// Функция отрисовки дороги
void drawRoad() {
    glColor3f(0.4f, 0.4f, 0.4f); // Серый цвет для дороги
    glBegin(GL_QUADS);
    glVertex3f(-15.0f, 0.0f, -55.0f);
    glVertex3f(-15.0f, 0.0f, 55.0f);
    glVertex3f(15.0f, 0.0f, 55.0f);
    glVertex3f(15.0f, 0.0f, -55.0f);
    glEnd();

    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex3f(-0.05f, 0.01f, -55.0f);
    glVertex3f(-0.05f, 0.01f, 55.0f);
    glVertex3f(0.05f, 0.01f, 55.0f);
    glVertex3f(0.05f, 0.01f, -55.0f);
    glEnd();

    glColor3f(0.1f, 0.8f, 0.1f);
    glBegin(GL_QUADS);
    glVertex3f(2.0f, 0.01f, -55.0f);
    glVertex3f(2.0f, 0.01f, 55.0f);
    glVertex3f(15.0f, 0.01f, 55.0f);
    glVertex3f(15.0f, 0.01f, -55.0f);
    glEnd();

    glColor3f(0.1f, 0.8f, 0.1f);
    glBegin(GL_QUADS);
    glVertex3f(-2.0f, 0.01f, -55.0f);
    glVertex3f(-2.0f, 0.01f, 55.0f);
    glVertex3f(-15.0f, 0.01f, 55.0f);
    glVertex3f(-15.0f, 0.01f, -55.0f);
    glEnd();
    float treesPositions[8][3] = {
        {-3, 0, -3},
        {-3, 0, 3},
        {3, 0, -3},
        {3, 0, 3},
        {3, 0, -9},
        {-3, 0, -9},
        {3, 0, -15},
        {-3, 0, -15}
    };
    // Рисуем деревья
    for (int i = 0; i < 8; ++i) {
        glPushMatrix();
        // Позиционируем дерево
        glTranslatef(treesPositions[i][0], treesPositions[i][1], treesPositions[i][2]);
        // Рисуем дерево
        drawTrees();

        glPopMatrix();
    }
}
void drawBridge() {
    glPushMatrix();
    glColor3f(0.6f, 0.3f, 0.0f); // Цвет моста
    glTranslatef(bridgeX, bridgeY, bridgeZ);
    glScalef(bridgeWidth, bridgeHeight, bridgeLength);
    glutSolidCube(1.0f);
    glPopMatrix();
    // Отрисовка наклонных частей моста
   // Наклонная часть в начале моста
    glPushMatrix();
    glColor3f(0.5f, 0.25f, 0.0f); // Цвет наклонных частей
    glTranslatef(bridgeX, bridgeY / 2, bridgeZ - (bridgeLength / 2 + rampLength / 2));
    glRotatef(-30.0f, 1.0f, 0.0f, 0.0f); // Наклон 30 градусов
    glScalef(bridgeWidth, bridgeHeight, rampLength);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Наклонная часть в конце моста
    glPushMatrix();
    glColor3f(0.5f, 0.25f, 0.0f); // Цвет наклонных частей
    glTranslatef(bridgeX, bridgeY / 2, bridgeZ + (bridgeLength / 2 + rampLength / 2));
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f); // Наклон 30 градусов
    glScalef(bridgeWidth, bridgeHeight, rampLength);
    glutSolidCube(1.0f);
    glPopMatrix();
}
// Функция для рисования цилиндра с крышкой
void drawWheel() {
    GLUquadricObj* quadratic;
    quadratic = gluNewQuadric();

    // Рисуем цилиндр (часть колеса)
    glColor3f(0.0f, 0.0f, 0.0f); // Черный цвет
    gluCylinder(quadratic, 0.1f, 0.1f, 0.2f, 32, 32);

    // Рисуем серую крышку
    glColor3f(0.5f, 0.5f, 0.5f); // Серый цвет
    gluDisk(quadratic, 0.0f, 0.1f, 32, 32);

    // Рисуем черное перекрестие (спицы)
    glColor3f(0.0f, 0.0f, 0.0f); // Черный цвет
    glBegin(GL_LINES);
    glVertex3f(-0.1f, 0.0f, 0.0f);
    glVertex3f(0.1f, 0.0f, 0.0f);
    glVertex3f(0.0f, -0.1f, 0.0f);
    glVertex3f(0.0f, 0.1f, 0.0f);
    glEnd();

    // Освобождаем объект квадрики
    gluDeleteQuadric(quadratic);
}

// Функция отрисовки автомобиля
void drawCar() {
    glPushMatrix();
    glTranslatef(carX, 0.0f, carZ);
    glRotatef(90, 0, 1, 0);
    glRotatef(carAngle, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(-0.76f, 0.25f, 0.4f);
    glVertex3f(-0.76f, 0.30f, 0.4f);
    glVertex3f(-0.76f, 0.30f, -0.4f);
    glVertex3f(-0.76f, 0.25f, -0.4f);
    glEnd();
    // Кузов автомобиля
    glColor3f(1.0f, 0.0f, 0.0f); // Красный цвет
    glBegin(GL_QUADS);
    glVertex3f(-0.75f, 0.15f, 0.5f);
    glVertex3f(0.75f, 0.15f, 0.5f);
    glVertex3f(0.75f, 0.15f, -0.5f);
    glVertex3f(-0.75f, 0.15f, -0.5f);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3f(-0.75f, 0.8f, 0.5f);
    glVertex3f(0.75f, 0.8f, 0.5f);
    glVertex3f(0.75f, 0.8f, -0.5f);
    glVertex3f(-0.75f, 0.8f, -0.5f);
    glEnd();
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.75f, 0.15f, 0.5f);
    glVertex3f(-0.75f, 0.4f, 0.5f);
    glVertex3f(0.75f, 0.15f, 0.5f);
    glVertex3f(0.75f, 0.4f, 0.5f);
    glVertex3f(0.75f, 0.15f, -0.5f);
    glVertex3f(0.75f, 0.4f, -0.5f);
    glVertex3f(-0.75f, 0.15f, -0.5f);
    glVertex3f(-0.75f, 0.4f, -0.5f);
    glVertex3f(-0.75f, 0.15f, 0.5f);
    glVertex3f(-0.75f, 0.4f, 0.5f);
    glEnd();
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.75f, 0.7f, 0.5f);
    glVertex3f(-0.75f, 0.8f, 0.5f);
    glVertex3f(0.75f, 0.7f, 0.5f);
    glVertex3f(0.75f, 0.8f, 0.5f);
    glVertex3f(0.75f, 0.7f, -0.5f);
    glVertex3f(0.75f, 0.8f, -0.5f);
    glVertex3f(-0.75f, 0.7f, -0.5f);
    glVertex3f(-0.75f, 0.8f, -0.5f);
    glVertex3f(-0.75f, 0.7f, 0.5f);
    glVertex3f(-0.75f, 0.8f, 0.5f);
    glEnd();
    glColor3f(0.0f, 0.4f, 0.9f);
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.75f, 0.4f, 0.5f);
    glVertex3f(-0.75f, 0.7f, 0.5f);
    glVertex3f(0.75f, 0.4f, 0.5f);
    glVertex3f(0.75f, 0.7f, 0.5f);
    glVertex3f(0.75f, 0.4f, -0.5f);
    glVertex3f(0.75f, 0.7f, -0.5f);
    glVertex3f(-0.75f, 0.4f, -0.5f);
    glVertex3f(-0.75f, 0.7f, -0.5f);
    glVertex3f(-0.75f, 0.4f, 0.5f);
    glVertex3f(-0.75f, 0.7f, 0.5f);
    glEnd();
    // Массив координат для позиционирования колёс
    float wheelPositions[4][3] = {
        {0.48f, 0.1f, 0.48f},  // Заднее левое колесо
        {-0.48f, 0.1f, 0.48f}, // Переднее левое колесо
        {-0.48f, 0.1f, -0.48f}, // Переднее правое колесо
        {0.48f, 0.1f, -0.48f}  // Заднее правое колесо
    };
    // Рисуем колёса
    for (int i = 0; i < 4; ++i) {
        glPushMatrix();
        // Позиционируем колесо
        glTranslatef(wheelPositions[i][0], wheelPositions[i][1], wheelPositions[i][2]);
        // Если это левое колесо, отражаем его
        if (i == 1 || i == 0) {
            glScalef(1.0f, 1.0f, -1.0f); // Отражение по оси X
        }
        // Рисуем колесо
        drawWheel();

        glPopMatrix();
    }
    glPopMatrix();
}

// Функция отрисовки
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Установка камеры на автомобиль
    gluLookAt(carX - camera_distance * sin(camera_angle_x),
        carY + camera_distance * 0.5,
        carZ - camera_distance * cos(camera_angle_x),
        carX, carY, carZ,
        0.0f, 1.0f, 0.0f);
    // Отрисовка дороги и деревьев
    drawRoad();
    drawCar();
    drawBridge();
    glutSwapBuffers();
}
// Функция для обработки специальных клавиш
void specialKeyPressed(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        keyStates['w'] = true;
        break;
    case GLUT_KEY_DOWN:
        keyStates['s'] = true;
        break;
    case GLUT_KEY_LEFT:
        keyStates['a'] = true;
        break;
    case GLUT_KEY_RIGHT:
        keyStates['d'] = true;
        break;
    }
}

// Функция для обработки отпускания специальных клавиш
void specialKeyUp(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        keyStates['w'] = false;
        break;
    case GLUT_KEY_DOWN:
        keyStates['s'] = false;
        break;
    case GLUT_KEY_LEFT:
        keyStates['a'] = false;
        break;
    case GLUT_KEY_RIGHT:
        keyStates['d'] = false;
        break;
    }
}

// Функция обновления игры
void update(int value) {
    if (keyStates['w']) { // Движение вперед
        carSpeed = 0.15f;
    }
    else if (keyStates['s']) { // Движение назад
        carSpeed = -0.075f;
    }
    else {
        // Здесь реализация плавного торможения
        deceleration = 0.001f; // Остановка движения при отпускании клавиши
    }

    if (keyStates['a']) { // Поворот влево
        carAngle += carTurnSpeed;
    }
    else if (keyStates['d']) { // Поворот вправо
        carAngle -= carTurnSpeed;
    }
    // Если скорость больше 0, замедляем автомобиль
    if (carSpeed > 0) {
        carSpeed -= deceleration;
        // Проверяем, не стала ли скорость меньше 0 после замедления
        if (carSpeed < 0) carSpeed = 0;
    }

    // Если скорость меньше 0, увеличиваем до 0 (для случая движения назад)
    if (carSpeed < 0) {
        carSpeed += deceleration;
        // Проверяем, не стала ли скорость больше 0 после ускорения
        if (carSpeed > 0) carSpeed = 0;
    }
    // Обработка движения автомобиля
    carZ += carSpeed * cos(carAngle * 3.14159265f / 180.0f);
    carX += carSpeed * sin(carAngle * 3.14159265f / 180.0f);

    // Ограничение автомобиля в пределах поля
    if (carX > 14.5f) carX = 14.5f;
    if (carX < -14.5f) carX = -14.5f;
    if (carZ > 54.5f) carZ = 54.5f;
    if (carZ < -54.5f) carZ = -54.5f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// Функция обработки клавиш
void keyboard(unsigned char key, int x, int y) {
    keyStates[key] = true; // Устанавливаем состояние клавиши в true
}
// Функция обработки отпускания клавиш
void keyboardUp(unsigned char key, int x, int y) {
    keyStates[key] = false; // Устанавливаем состояние клавиши в false
}

// Обработчик движения мыши
void mouseMove(int x, int y) {
    static int last_x = -1;
    static int last_y = -1;
    if (last_x == -1 && last_y == -1) {
        last_x = x;
        last_y = y;
    }
    // Рассчитываем изменение позиции мыши
    int dx = x - last_x;
    int dy = y - last_y;
    // Обновляем углы камеры
    camera_angle_x += dx * 0.1f;
    camera_angle_y += dy * 0.1f;
    // Сохраняем текущую позицию мыши
    last_x = x;
    last_y = y;
    // Обновляем сцену
    glutPostRedisplay();
}

// Обработчик нажатий кнопок мыши
void mouseButton(int button, int state, int x, int y) {
    // Проверяем, нажата ли кнопка колесика мыши
    if (button == 3 || button == 4) {
        if (state == GLUT_UP) return; // Игнорируем события отпускания кнопки
        // Приближаем или отдаляем камеру
        camera_distance += (button == 3) ? -0.1f : 0.1f;
        // Обновляем сцену
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Car Driving Simulator");

    glutDisplayFunc(display);
    glutTimerFunc(10, update, 0);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialKeyPressed);
    glutSpecialUpFunc(specialKeyUp);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.5f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, 1.333f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);

    glutMainLoop();
    return 0;
}

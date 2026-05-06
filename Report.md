---
title: Interactive Spaceship Controller - OpenGL C++ Implementation
tags:
  - study
  - exam
  - OpenGL
  - CPP
date: 2026-05-06T18:18:00
status: studying
format: obsidian-md
---
## 1) Libraries and Setup Configuration

### Detailed Explanation

الـ Code بيبدأ بتعريف مجموعة من الـ Header files الأساسية علشان الـ Rendering والعمليات الحسابية.
الـ `<GL/glut.h>` هو المسؤول عن الـ Window management والـ Graphics rendering باستخدام OpenGL.
الـ `<math.h>` بيوفر العمليات الحسابية زي الـ `sin` والـ `cos` اللي بتستخدم في الـ Rotations ورسم الدواير.
الـ `<string>` والـ `<sstream>` والـ `<iomanip>` بيستخدموا علشان معالجة النصوص وتجهيز الـ Data اللي هتتعرض على الشاشة زي الـ Position والـ Scale.
الـ `<stdlib.h>` بيوفر دوال زي `()rand` علشان توليد أرقام عشوائية.
الـ `<vector>` بيعمل Dynamic array علشان يخزن بيانات الـ Lasers اللي بتضرب.

> [!TIP]  
> الجزء دا بيأسس الـ Environment اللي الـ Code هيشتغل عليها من مكتبات وثوابت.

الـ Constant المسمى `PI` متعرف بقيمة `3.14159265f` علشان الحسابات الهندسية الخاصة بالزوايا.

الـ Global Variables بتنقسم لأكتر من جزء:
متغيرات الـ Transformations للصاروخ بتشمل `posX` و `posY` وقيمتهم الابتدائية `0.0f`.
الـ `angle` بتبدأ بـ `0.0f`، والـ `scale` بيبدأ بـ `1.0f`، والـ `shearX` بيبدأ بـ `0.0f`.

متغيرات الـ Animation والـ Logic بتشمل `flameTime` علشان حركة النار وقيمته `0.0f`، والـ `fireCooldown` وقيمته `0` علشان يتحكم في سرعة ضرب الـ Laser.

متغيرات الشاشة `screenW` قيمتها `800.0f` والـ `screenH` قيمتها `600.0f`.

الـ Arrays الخاصة بالـ Input هي `keys[256]` للزراير العادية و `specialKeys[256]` للـ Arrows، وكلهم بيبدأوا بـ `false`.

> [!NOTE]  
> الـ Arrays دي بتشتغل كـ State flags علشان تسجل الزرار المضغوط حاليًا.

الـ Data Structures بتشمل `struct Star` جواه `x` و `y` و `size` و `speed` و `brightness`.
الـ Array المسمى `stars[200]` بيخزن 200 نجمة.

الـ `struct Laser` جواه `x` و `y` و `dx` و `dy` و `angle` و `scale` و `active`.
الـ `std::vector<Laser> lasers` بيخزن كل الـ Lasers اللي بيتم إطلاقها.

### Key Points Summary

- الـ `PI` معرف بـ `3.14159265f`.
- عدد النجوم الثابت هو 200 نجمة في الـ `stars` array.
- الـ `lasers` متخزنة في Dynamic `std::vector`.
- الـ Screen بتبدأ بأبعاد `800.0f` للـ `screenW` و `600.0f` للـ `screenH`.

> [!tip]  
> دايماً إفتكر إن المتغيرات الخاصة بالمكان والزوايا بتبدأ من نقطة الأصل `(0, 0)` وبـ Scale طبيعي `1.0f`.

### Definitions

- `<GL/glut.h>`: 
	دي هيا ال Library للتعامل مع الـ OpenGL والـ Window System.
- `std::vector`:
	عبارة عن Dynamic Array بيغير حجمه وقت الـ Runtime.
- `struct`:
	دا Data Structure بتجمع متغيرات مختلفة تحت اسم واحد.

### Rules / Laws / Principles

- Array Size Rule
- أي Array للزراير `keys` و `specialKeys` لازم يكون حجمه 256 علشان يغطي كل الـ ASCII characters.
- لا توجد شروط معقدة، فقط الحجم ثابت. ومفيش أي استثناءات.
### Step-by-Step Process

1. استدعاء الـ Libraries المطلوبة.
2. تعريف ثابت الـ `PI`.
3. تعريف الـ Global Variables للـ Position والـ Window.
4. تعريف الـ `struct` للنجوم والليزرات وتجهيز الـ Arrays/Vectors الخاصة بيهم.

### Examples

مفيش أمثلة تطبيقية في الجزء دا لأنه مخصص للـ Setup بس.

### Common Mistakes / Traps

- نسيان عمل Initialize للـ `keys` بـ `false` ممكن يعمل Ghost inputs.

> [!WARNING]  
> لو الـ Flags دي مش `false`، الـ Spaceship هيتحرك لوحدا بمجرد تشغيل البرنامج.

### High-Risk Exam Content

- القيم الابتدائية للـ `scale` هي `1.0f` مش `0.0f`، لو بقت زيرو الصاروخ هيختفي.
- الـ `fireCooldown` بيبدأ بـ `0` علشان يسمح بالضرب فوراً.
### Exam-Style Questions

>[!CAUTION] 
>**Q1 :**
> What are the default dimensions of the screen variables?

>[!IMPORTANT]
> **Answer :**
> `screenW = 800.0f` and `screenH = 600.0f`.

>[!CAUTION]
> **Q2 :**
> Which library provides the dynamic array functionality for the lasers?

>[!IMPORTANT] 
>**Answer :**
>The `<vector>` library.

---
## 2) Drawing Functions Implementation

### Detailed Explanation

الدالة `drawText` بتاخد الإحداثيات `x` و `y` ونوع الـ `font` والـ `text` نفسه، بالإضافة لدرجات الألوان `r`, `g`, `b`.
الدالة بتستخدم `glColor3f` علشان تحدد لون النص.
وبتستخدم `glRasterPos2f` علشان تحدد مكان بداية الكتابة.
وبعدين بتعمل Loop على كل `char c` في الـ `text` وترسمه باستخدام `glutBitmapCharacter`.

> [!IMPORTANT]  
> الـ Text بيترسم حرف بحرف باستخدام Loop على الـ String.

الدالة `drawCircle` بتاخد الـ `radius` والـ Center `cx`, `cy` وعدد الـ `segments`.
بتبدأ بـ `glBegin(GL_POLYGON)` علشان ترسم مضلع مقفول.
بتعمل Loop من 0 لحد `segments` وتحسب الزاوية `theta` لكل نقطة.
الـ `theta` بتتحسب بمعادلة $2.0f * PI * float(i) / float(segments)$.
بترسم كل نقطة بـ `glVertex2f` باستخدام الـ `cosf` للـ `x` والـ `sinf` للـ `y` ومضروبين في الـ `radius` ومجموع عليهم المركز `cx` و `cy`.
بتنتهي بـ `()glEnd`.

الدالة `drawRoundedRect` بترسم مستطيل بحواف دائرية وبتاخد الـ `x`, `y`, `w`, `h`, `r` (الـ radius بتاع الحافة) وقيمة `filled` (boolean).
وعدد الـ `segments` لكل زاوية ثابت وهو 10.
لو `filled` بـ `true` بتستخدم `GL_POLYGON`، ولو `false` بتستخدم `GL_LINE_LOOP`.
الرسم بيتم على 4 مراحل (4 Loops)، كل مرحلة بترسم ربع دايرة في كورنر مختلف باستخدام حسابات المثلثات وإضافة $PI/2$ لكل كورنر.

الدالة `drawSpaceship` بترسم الصاروخ نفسه.
بتعرف متغير `flicker` وتدي له قيمة $sinf(flameTime) * 10.0f$ علشان تعمل حركة للنار.
وبترسم النار الخلفية بلون برتقالي `glColor3f(1.0f, 0.2f, 0.0f)` باستخدام `GL_TRIANGLES` والـ `flicker` بيأثر على الـ `y` بتاعت آخر نقطة تحت.
وبترسم نار تانية أصغر بلون أصفر باستخدام نفس الـ `flicker` مضروب في `0.5f`. وبترسم جناحات الصاروخ بلون أحمر غامق باستخدام `GL_TRIANGLES`.
وبترسم جسم الصاروخ بلون أبيض مائل للرمادي باستخدام `GL_QUADS`. وبترسم مقدمة الصاروخ بمثلث أحمر فوق الجسم.
وفي النهاية بترسم شبابيك الصاروخ باستخدام دالة `drawCircle` بألوان رمادية وسماوية (Cyan).

> [!important]  
> دالة الـ `drawSpaceship` بتعتمد كلياً على الـ Relative coordinates حوالين النقطة `(0,0)`، دا بيسمح بتطبيق الـ Transformations عليها كقطعة واحدة بعدين.

### Key Points Summary

- الـ `glutBitmapCharacter` هي المسؤولة عن رسم الحروف.
- الـ `drawCircle` بتعتمد على `GL_POLYGON` وتقسيم الزاوية $2*PI$ على الـ `segments`.
- الـ `flicker` بيعمل أنيميشن للنار باستخدام دالة الـ `sinf`.
- الـ `drawRoundedRect` بتجمع 4 أقواس مع بعض علشان تكون الشكل.

> [!tip]  
> لو طلب منك تزود نعومة الدايرة في الامتحان، هتزود قيمة الـ `segments`.

### Definitions

- `GL_POLYGON`:
	ال Primitive في OpenGL بيوصل كل النقط ببعض علشان يعمل شكل مقفول ومتلون من جوا.
- `GL_LINE_LOOP`:
	لPrimitive بيرسم خطوط بين النقط وبيقفل الشكل في الآخر بخط بين آخر وأول نقطة.
- `glRasterPos2f`:
	دالة بتحدد الـ Raster Position اللي هيبدأ من عند رسم الـ Text.

### Rules / Laws / Principles

- Primitive Selection Rule
- لو الشكل مطلوب يكون مليان لون `filled == true` بيتم اختيار `GL_POLYGON`.
- لو مطلوب إطار بس بيتم اختيار `GL_LINE_LOOP`.
- دا بيتحكم في شكل الـ Rendering النهائي.
- ومفيش استثناءات في الكود دا.
### Formulas / Equations
==> $theta = 2.0f * PI * float(i) / float(segments)$

- `theta`:
	الزاوية بالـ Radian للنقطة الحالية.
- `i`:
	رقم النقطة (الـ Iteration).
- `segments`:
	عدد النقط الكلي اللي بيكون الدايرة.


==> $flicker = sinf(flameTime) * 10.0f$

- `flicker`:
	مقدار التذبذب في طول النار.
- `flameTime`:
	المتغير اللي بيزيد مع الوقت علشان يحرك دالة الـ Sine.
- `10.0f`:
	مقدار الـ Amplitude (أقصى امتداد للنار).

### Step-by-Step Process

1. رسم الدواير بيتم بتحديد المركز والـ Radius
2. حساب الـ Angle لكل نقطة على المحيط.
3. تحديد مكان النقطة بـ `cos` للـ X و `sin` للـ Y.
4. إرسال النقط للـ OpenGL بـ `glVertex2f`.
5. إنهاء الرسم بـ `glEnd`.
### Examples

- رسم الشباك بـ `drawCircle(10, 0, 0, 30)` بيرسم دايرة نصف قطرها 10 عند نقطة الأصل بعدد 30 شريحة.    
### Common Mistakes / Traps

- استخدام `GL_TRIANGLES` لعمل الدايرة بدل `GL_POLYGON` هيخلي الدايرة تترسم بشكل مش مظبوط لو متمركزتش النقط صح.
- نسيان إضافة الـ Center `cx` و `cy` في معادلة الدايرة بيخلي كل الدواير تترسم في نص الشاشة بغض النظر عن المكان المطلوب.
   

> [!CAUTION]
> 
> لو تم استدعاء `()glEnd` قبل ما تخلص كل النقط في الـ Loop، الشكل هيطلع مقطوع.

### High-Risk Exam Content

- معادلة النقطة في الدايرة: $;glVertex2f(radius * cosf(theta) + cx, radius * sinf(theta) + cy)$.
- نوع الـ Primitive المستخدم في رسم جسم الصاروخ هو `GL_QUADS`.

### Exam-Style Questions

>[!CAUTION] 
>**Q1 :**
>What primitive is used to draw the main body of the spaceship?

>[!IMPORTANT] 
>**Answer :**
>`GL_QUADS`.

>[!CAUTION] 
>**Q2 :**
>How is the flicker effect of the spaceship's flame calculated?

>[!IMPORTANT] 
>**Answer :**
>By applying the sine function to `flameTime` and multiplying it by an amplitude of `10.0f`.

---
## 3) Background and User Interface (UI)

### Detailed Explanation

الدالة `drawBackgroundAndUI` بتبدأ بعمل Loop على 200 نجمة. بتحدد لون كل نجمة باستخدام `stars[i].brightness` للثلاث قيم R, G, B علشان تطلع درجات رمادي/أبيض. وبتحدد حجم النقطة بـ `glPointSize(stars[i].size)` وبترسم النقط بـ `GL_POINTS`.

> [!TIP]
> 
> الجزء دا مسؤول عن رسم الفضاء الخلفي الثابت والمتحرك، والواجهة اللي بتعرض البيانات للمستخدم.

بعدها بيتم حساب إحداثيات القمر `moonX` و `moonY` بناءً على أبعاد الشاشة. الـ X بيبقى على الشمال والـ Y فوق. وبيتم تفعيل الـ Alpha Blending بـ `glEnable(GL_BLEND)` واستخدام `glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)`.

بيترسم 10 دواير شفافة فوق بعض بأحجام بتقل تدريجياً علشان يعمل تأثير الوهج (Glow) للقمر باستخدام `drawCircle`. وبيتم إيقاف الـ Blending بـ `glDisable(GL_BLEND)`.

وبيترسم جسم القمر الأساسي وبعدين بتترسم 3 دواير صغيرة بألوان أغمق شوية علشان تمثل الفوهات (Craters) على سطح القمر. والـ UI Panels بتترسم في الجزء السفلي. وبيتم تفعيل الـ Blending تاني علشان الـ Panels تكون نصف شفافة. الـ Panel الشمال مخصصة للـ `KEYBOARD CONTROLS`.

وبتترسم بـ `drawRoundedRect` مليانة بلون أزرق غامق شفاف، وفوقها إطار بلون أزرق فاتح. بيترسم خط تحت العنوان بـ `GL_LINES`. وبيتم طباعة التعليمات باستخدام دالة `drawText` وبفونت `GLUT_BITMAP_HELVETICA_12`.

الألوان بتتغير، مثلاً زرار الـ SPACE بيبقى لونه برتقالي والـ ESC لونه أحمر. والـ Panel اليمين مخصصة للـ `CURRENT STATUS`.

بتترسم بلون أخضر غامق شفاف وإطار أخضر فاتح. البيانات الديناميكية زي الـ Position، Angle، Scale، و Shear بتتجهز باستخدام `std::stringstream` علشان يتم دمج النصوص مع الأرقام بدقة `setprecision(2)`.

بتترسم كل البيانات ورا بعض، وفي النهاية بتطبع كلمة `Active` باللون الأخضر علشان توضح حالة الـ Rendering. وفي النهاية بيتم تعطيل الـ Blending تماماً.

> [!IMPORTANT]
> 
> استخدام الـ `stringstream` ضروري جداً لتحويل الأرقام الـ `float` لنصوص نقدر نبعتها لدالة الـ `drawText`.

### Key Points Summary

- القمر ليه تأثير Glow بيتعمل بـ 10 دواير متداخلة بشفافية متدرجة.

- الـ Blending ضروري لتأثير الشفافية في القمر والـ UI Panels.
  
- دالة `std::setprecision(2)` بتخلي الأرقام تتعرض بعلامتين عشريتين بس.

- الـ UI Panels متمركزة بناءً على أبعاد الشاشة الحالية `screenW` و `screenH`.
    
> [!tip]
> 
> لو الشاشة اتغير حجمها، الـ UI هتفضل في مكانها تحت يمين وشمال لأنها مربوطة بنسب `screenW/2` و `screenH/2`.

### Definitions

- `GL_BLEND`:
	خاصية في OpenGL بتسمح بدمج لونين مع بعض لإنتاج الشفافية (Transparency).
- `glBlendFunc`:
	دالة بتحدد معادلة دمج الألوان للشفافية.
- `std::stringstream`: 
	كلاس في ++C بيتعامل مع الـ Strings كأنها Streams، ودا بيسهل دمج المتغيرات فيها.
### Rules / Laws / Principles

- Blending Enable/Disable Rule
- لازم تفعل الـ Blending بـ `glEnable(GL_BLEND)` قبل رسم أي حاجة شفافة.
- لازم توقف الـ Blending بـ `glDisable(GL_BLEND)` بعد ما تخلص علشان باقي الأشكال متتأثرش وتبقى شفافة بالغلط.
- ومفيش استثناءات.

### Step-by-Step Process

1. حساب أبعاد الـ Panels (العرض والطول).
2. تحديد الـ X و Y للركن السفلي الشمال.
3. رسم خلفية الـ Panel الشفافة.
4. رسم الإطار الخارجي للـ Panel.
5. رسم النصوص التعليمية والبيانات بمسافات متساوية `step`.
### Examples

- طباعة الـ Scale Factor: بتتم عن طريق وضع القيمة في الـ `stringstream` بالشكل دا: 
`s << "Scale Factor: " << scale << "x";`
وبعدين تمرير الـ `()s.str` لدالة الرسم.

### Common Mistakes / Traps

- رسم الـ Background الشفافة من غير ما تفعل الـ `GL_BLEND` هيخليها تترسم كأنها Solid colour.

> [!WARNING]
> 
> ترتيب تشغيل وإيقاف الـ Blending مهم جدًا، الغلطة فيه بتبوظ الـ Rendering بالكامل.

### High-Risk Exam Content

- الدالة المسؤولة عن تفعيل الـ Blending هي `glEnable(GL_BLEND)`.
- معادلة الـ Blending المستخدمة هي `glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)`.

### Exam-Style Questions

>[!CAUTION] 
>**Q1 :**
>What OpenGL function and state are required to draw the semi-transparent UI panels?

>[!IMPORTANT]
>**Answer :**
>`glEnable(GL_BLEND)` and `glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)`.

>[!CAUTION] 
>**Q2 :**
>How many decimal places are displayed for the X and Y positions in the UI?

>[!IMPORTANT]
>**Answer :**
>Two decimal places, enforced by `std::setprecision(2)`.

---
## 4) Rendering Logic and Camera Setup

### Detailed Explanation

الدالة `drawLasers` بتعمل Loop على كل عناصر الـ `lasers` vector.

لو الـ Laser كان `active`، بتستخدم `()glPushMatrix` علشان تعزل التعديلات عن باقي الأشكال. بتنقل الـ Laser لمكانه بـ `glTranslatef(lasers[i].x, lasers[i].y, 0.0f)`. وبتعمل دوران للـ Laser بـ `glRotatef(lasers[i].angle, 0.0f, 0.0f, 1.0f)`.

بتعمل سكيل ليه بـ `glScalef(lasers[i].scale, lasers[i].scale, 1.0f)`. وبترسم الـ Laser كلون سماوي `(0,1,1)` كـ `GL_QUADS` (مستطيل طويل). بترجع للـ Matrix الأصلي بـ `()glPopMatrix`.

> [!important]
> 
> **ترتيب العمليات في OpenGL عكسي نظريًا، لكن في الكود بيتكتب: Translate ثم Rotate ثم Scale.**
> يعني في الـ OpenGL، الـ Transformations بتتنفذ على الأوبجكت من **الأسفل للأعلى** (Last called, first applied). يعني لو الكود مكتوب: Translate ثم Rotate ثم Scale، الـ OpenGL هيعمل Scale للأوبجكت الأول، وبعدين يلفه (Rotate)، وفي الآخر يحركه لمكانه (Translate).

الدالة `display` هي الـ Main rendering callback.

بتمسح الـ Buffer بـ `glClear(GL_COLOR_BUFFER_BIT)`. وبتنادي `()drawBackgroundAndUI` و `()drawLasers`.

بتبدأ ترسم الصاروخ: بتستخدم `()glPushMatrix`. وبتطبق الـ Translate بـ `posX` و `posY`. وبتطبق الـ Rotate بـ `angle` على محور Z.

بتطبق الـ Scale بـ `scale`. وبتطبق الـ Shear X عن طريق تعريف `shearMatrix` عبارة عن 16 رقم. الرقم اللي في الاندكس 4 هو الـ `shearX`. وبتضرب الـ Matrix دي باستخدام `glMultMatrixf(shearMatrix)`.

بتنادي `()drawSpaceship` وبعداا `()glPopMatrix`. وبتخلص وتعرض الـ Frame بـ `()glutSwapBuffers`.

الدالة `reshape` بتشتغل لما حجم الويندو يتغير. بتاخد العرض `w` والطول `h`. وفي حالة `h == 0` بتخليه 1 علشان تمنع الـ Division by Zero.

بتحدث الـ `screenW` والـ `screenH`. وبتظبط الـ `glViewport(0, 0, w, h)`.

بتعدل الكاميرا: `glMatrixMode(GL_PROJECTION)` وبتمسح الـ Matrix بـ `()glLoadIdentity`. وبتظبط الـ 2D Orthographic Projection بـ `gluOrtho2D` بحيث النقطة `(0,0)` تكون في نص الشاشة بالضبط من `-screenW/2` لـ `screenW/2` وهكذا للـ Y. وبترجع تاني لـ `glMatrixMode(GL_MODELVIEW)`.
### Key Points Summary

- الـ `glPushMatrix` والـ `glPopMatrix` بيستخدموا علشان يمنعوا تسرب الـ Transformations بين الأشكال المختلفة.
- الـ Shear Transformation بيتعمل بـ Custom Matrix مش بـ Function جاهزة في OpenGL.
- الـ `gluOrtho2D` هي المسؤولة عن تحديد نظام الإحداثيات بحيث النص يكون `(0,0)`.
- الـ `glutSwapBuffers` مسؤولة عن عرض الرسمة النهائية في الـ Double Buffering.

> [!tip]
> 
> دايماً اربط الـ `GL_PROJECTION` بإعدادات الكاميرا والعدسة، واربط الـ `GL_MODELVIEW` بحركة الأشكال نفسها جوا العالم.

### Definitions

- `glPushMatrix`:
	بتحفظ الحالة الحالية للـ Matrix في الـ Stack.
- `glPopMatrix`:
	بتسترجع آخر حالة للـ Matrix من الـ Stack وتلغي أي تأثيرات اتعملت بعداا.
- `glMultMatrixf`:
	بتضرب الـ Matrix الحالية في مصفوفة محددة الـ User بيديها.
- `gluOrtho2D`:
	بتعمل إسقاط ثنائي الأبعاد (Orthographic) يعني مفيش منظور ثلاثي الأبعاد والعمق مبيأثرش على الحجم.

### Rules / Laws / Principles

- Push and Pop Pairing Rule
- كل استدعاء لـ `glPushMatrix` لازم يقابله استدعاء لـ `glPopMatrix`.
- لو العدد مش متساوي الـ Stack هيحصله Overflow أو Underflow والبرنامج هيكراش.
- ومفيش استثناءات.

### Formulas / Equations

```cpp
float shearMatrix[16] = {
    1.0f, 0.0f, 0.0f, 0.0f, 
    shearX, 1.0f, 0.0f, 0.0f, 
    0.0f, 0.0f, 1.0f, 0.0f, 
    0.0f, 0.0f, 0.0f, 1.0f
};
```

- دي الـ Column-Major Order Matrix اللي OpenGL بيستخدمها.
- قيمة الـ `shearX` بتتحط في مكان بيخلي محاور الـ X تميل مع زيادة الـ Y.

### Step-by-Step Process

1. تغيير وضع الـ Matrix لـ Projection في الـ `reshape`.
2. عمل Reset للـ Matrix بـ Identity.
3. تعريف إحداثيات المشهد بـ Ortho2D.
4. العودة لوضع الـ ModelView علشان رسم الأشكال.
### Examples

- لما الـ `shearX` بيزيد، الصاروخ بيميل للجنب كأنه بيتسحب من فوق، ودا ناتج عن الـ Matrix multiplication.
### Common Mistakes / Traps

- نسيان كتابة `glMatrixMode(GL_MODELVIEW)` في آخر دالة `reshape` هيخلي أي `glTranslatef` أو تغييرات تتطبق على الكاميرا بدل الأشكال، ودا هيبوظ الرسم بالكامل.

> [!CAUTION]
> الـ Division by Zero في حساب الـ Aspect Ratio أو الإحداثيات لو الـ Window ارتفاعها بقى 0 ممكن يعمل Crash، علشان كدا فيه شرط `;if (h == 0) h = 1`.

### High-Risk Exam Content

- مكان وضع معامل القص `shearX` في المصفوفة: في الـ Index رقم 4 في الـ 1D array الممثلة للـ 4x4 matrix.
- استخدام `glutSwapBuffers` بدلاً من `glFlush` بسبب استخدام `GLUT_DOUBLE` في الـ `main`.
### Exam-Style Questions

>[!CAUTION] 
>**Q1 :**
>Why is `shearMatrix` defined as an array of 16 floats?

>[!IMPORTANT]
>**Answer :**
>Because OpenGL uses a 4x4 transformation matrix stored as a 1D array in column-major order.

>[!CAUTION]
>**Q2 :**
>Which function displays the final rendered frame in this double-buffered program?

>[!IMPORTANT]
>**Answer :**
>`glutSwapBuffers()`.

---
## 5) Input Handling and Physics Logic

### Detailed Explanation

الدالة `handleContinuousMovement` هيا المسؤولة عن تحديث قيم المتغيرات بناءً على حالة الزراير في الـ Arrays (`keys` و `specialKeys`). وسرعة الحركة `moveSpeed` ثابتة عند `5.0f`.

لو الـ UP السهم مضغوط، `posY` بتزيد. لو DOWN، بتقل. لو LEFT، `posX` بتقل. لو RIGHT، بتزيد. لو حرف A مضغوط، الـ `angle` بيزيد 3 درجات. لو حرف D مضغوط، الـ `angle` بيقل 3 درجات. حرف W بيزود الـ `scale` بمقدار `0.02f`.

حرف S بيقلل الـ `scale`، بس فيه شرط `if (scale > 0.2f)` علشان الصاروخ ميختفيش أو يقلب. الـ Q والـ E بيغيروا الـ `shearX` بالسالب والموجب. الـ R بتعمل Reset لكل حاجة (Position 0، Angle 0، Scale 1، Shear 0) وبتعمل `()lasers.clear` علشان تمسح كل الليزر اللي في الشاشة.

> [!TIP]
> الضرب بالـ SPACE بيحصل بس لو الـ `fireCooldown == 0`.
 
لما الـ SPACE تتضغط والـ Cooldown يسمح، بيتم حساب مكان وزاوية خروج الليزر. بيحول الـ `angle` لـ `rad` بالراديان عن طريق `angle * PI / 180.0f`. ,بيحسب نقطة خروج الليزر Local للصاروخ (مقدمة الصاروخ) بـ `localNoseX = 80.0f * shearX * scale` و `localNoseY = 80.0f * scale`.

بيطبق حساب المثلثات علشان ينقل النقطة دي للـ Global coordinates في الـ الشاشة بناءً على دوران الصاروخ الحالي. بيحسب اتجاه الليزر `dirX` و `dirY` بناءً على الـ Shear والـ Angle، وبعدين بيعملهم Normalization (يقسمهم على الـ length) علشان سرعة الليزر تكون ثابتة. الزاوية بتاعة الليزر `laserAngle` بتتحسب بـ  $atan2f(dirY, dirX) * 180.0f / PI - 90.0f$.

,بيدور في الـ `lasers` vector، لو لقى ليزر مش `active`، بيعيد استخدامه (Object Pooling) ويحط فيه البيانات الجديدة. لو ملقاش، بيعمل `push_back` لليزر جديد. بيخلي الـ `fireCooldown = 5` علشان ميضربش ليزر ورا بعض في نفس الفريم.

الدالة `timer` بتتنفذ كل فترة زمنية. بتقلل الـ `fireCooldown` بمقدار 1 لحد ما يوصل لـ 0. بتزود الـ `flameTime` بمقدار `0.5f`.

,بتنادي على `()handleContinuousMovement`. ,بتعمل Loop على النجوم علشان تنزلهم لتحت بـ `stars[i].y -= stars[i].speed`. لو النجمة خرجت برا الشاشة تحت، بترجعها فوق خالص `screenH/2.0f` وبتحطها في `x` عشوائي. وبتغير لمعان النجمة كل فريم. بتعمل Loop على الليزر الفعال وبتجمع الـ `dx` و `dy` على الـ `x` و `y`.

ولو الليزر خرج برا الشاشة بيتحول لـ `active = false`. وبتنادي `()glutPostRedisplay` علشان ترسم الفريم الجديد. وبتنادي نفسها تاني `glutTimerFunc(30, timer, 0)` علشان تتنفذ كمان 30 ملي ثانية.

والدوال `keyboardDown` و `keyboardUp` و `specialDown` و `specialUp` بيعدلوا في الـ arrays بـ `true` و `false`. ولو الزرار `27` (وهو الـ ESC) اتضغط، بيعمل `exit(0)`.

### Key Points Summary

- الحركة مستمرة لأنها بتعتمد على Arrays بتسجل حالة الزرار مش بس حدث الضغط.
- الـ Laser بيعتمد على Object Pooling، يعني إعادة استخدام ليزر منتهي الصلاحية بدل من إنشاء جديد دايماً لتوفير الميموري.
- الليزر بيتمسح (بيبقى Inactive) لو خرج بره حدود الشاشة تماماً.
- الـ Timer بيشتغل بمعدل 30ms يعني تقريباً 33 Frame Per Second.

> [!tip]
> 
> لو عايز تسرع حركة اللعبة كلها بتقلل الرقم `30` في الـ `glutTimerFunc`.

### Definitions

- Object Pooling:
	تقنية لإعادة استخدام كائنات موجودة في الذاكرة ومطفية بدل من إنشاء وتدمير كائنات جديدة طول الوقت يعني بنستخدمه هنا علشان نتفادى الـ Memory Allocation المستمر (يعني بنتجنب استخدام `new` و `delete` في كل فريم)، ودا بيحسن أداء الـ Frame Rate جداً (Performance Optimization).
- Normalization:
	تحويل المتجه (Vector) بحيث يكون طوله 1 مع الاحتفاظ باتجاهه، بيتعمل بقسمة المركبات على طول المتجه.
- Cooldown:
	فترة انتظار إجبارية بين أكشن والتاني، بتستخدم هنا لضبط معدل الضرب.
### Rules / Laws / Principles

- Scale Limit Rule
- فيه شرط يمنع أن الـ Scale يقل عن `0.2f`.
- الهدف منه منع اختفاء المجسم أو تحوله للسالب وانعكاسه.
### Formulas / Equations

$rad = angle * \frac{PI}{180.0f}$

- التحويل من درجات (Degrees) لزوايا نصف قطرية (Radians) علشان دالة الـ `sinf` والـ `cosf` بتاخد Radians.

Code snippet

$len = \sqrt{dirX^2 + dirY^2}$

- `len`:
	طول متجه الاتجاه.
$laserAngle = atan2f(dirY, dirX) * \frac{180.0f}{PI} - 90.0f$


- `atan2f`:
	بتجيب الزاوية بناء على X و Y في كل الأرباع. بتضرب في 180 وبتتقسم على PI للتحويل لدرجات. بيتم طرح 90 درجة لتعديل الاتجاه ليناسب الـ Up Vector.
### Step-by-Step Process

1. التأكد من حالة زرار المسطرة والـ Cooldown.
2. حساب مكان نقطة انطلاق الليزر باستخدام الـ Scale والـ Shear والـ Angle.
3. تحديد متجه اتجاه الليزر وعمل Normalization له.
4. حساب زاوية دوران شعاع الليزر.
5. البحث عن ليزر قديم غير مفعل واستخدامه، أو إضافة واحد جديد للـ Array.
### Examples

- لما تضغط مسطرة والـ Cooldown 0، الصاروخ بيحسب التدوير اللي هو واخدا وبيطلق الليزر في نفس اتجاه الدوران، والـ Cooldown بيبقى 5، ومع كل فريم بينقص 1 لحد ما يرجع 0 وتقدر تضرب تاني بعد 150 ملي ثانية (5 * 30ms).

### Common Mistakes / Traps

- نسيان عمل `active = false` لليزر لما يخرج برا الشاشة هيخلي الـ `vector` يكبر للما لا نهاية والبرنامج يستهلك الميموري كلها ويهنج.

> [!TIP]
> الـ `keys[key] = true` من غير الـ `keyboardUp` اللي بتعمله `false` هيخلي الحركة متقفش أبداً حتى لو شيلت إيدك من على الزرار.

### High-Risk Exam Content

- الزاوية في معادلة اتجاه الليزر بيتم استخدام `atan2f` مش `atan` العادية علشان تظبط الزاوية في الـ 4 أرباع الدائرية.
- استخدام $localNoseY = 80.0f * scale$، الرقم 80 جاي من طول مقدمة الصاروخ.
### Exam-Style Questions

>[!CAUTION] 
>**Q1 :**
>What happens when the `R` key is pressed?

>[!IMPORTANT]
>**Answer :**
>The spaceship's position, angle, scale, and shear are reset to their default values, and the active lasers vector is cleared.

>[!CAUTION]
>**Q2 :**
>How is memory efficiency managed when firing lasers?

>[!IMPORTANT] 
>**Answer :**
>The code iterates through existing lasers to find an inactive one to reuse before creating and pushing a new laser object into the vector.

---
## 6) Initialization and Main Loop

### Detailed Explanation

الدالة `init` بتبدأ بـ `glClearColor(0.01f, 0.02f, 0.05f, 1.0f)` علشان تحدد لون الشاشة لما تتعملها Clear (لون الخلفية هنا أزرق غامق جداً يميل للأسود). بتعمل Loop لعمل Initialize للنجوم، بتديهم مواقع عشوائية `x` و `y` في مساحات واسعة (-1000 لـ 1000) للـ X.

وبتديهم أحجام وسرعات عشوائية مختلفة علشان تديهم تأثير الـ Parallax (النجوم القريبة أسرع من البعيدة). والدالة `main` هي نقطة البداية لأي برنامج ++C.

وبتعمل `glutInit(&argc, argv)` لتهيئة مكتبة GLUT. وبتضبط وضع العرض بـ `glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_ALPHA)`.

`GLUT_DOUBLE`
	بتفعل الـ Double Buffering لمنع الـ Flickering أثناء الرسم. `GLUT_RGB` لنظام الألوان و `GLUT_ALPHA` علشان يدعم الشفافية. بتحدد حجم الويندو بـ `glutInitWindowSize(screenW, screenH)`.

وبتعمل كرييت للويندو باسم `"INTERACTIVE SPACESHIP CONTROLLER"`. بتنادي على الدالة `()init`.

وبتربط الـ Callbacks بالـ Events: دالة `display` للرسم، و `reshape` لتغيير الحجم، و `keyboardDown`/`Up` و `specialDown`/`Up` للزراير، و `timer` كـ Timer بصفر علشان يشتغل فوراً أول مرة. وأخيراً بتنادي `()glutMainLoop` اللي بتدخل البرنامج في حلقة لانهائية مبيخرجش منها إلا بقفل الويندو أو ضغط ESC.

> [!TIP]
> 
> الجزء دا بيربط كل الـ Components مع بعض ويسلم التحكم لـ OpenGL ومكتبة GLUT علشان يشغل اللعبة.

### Key Points Summary

- الدالة `main` بتعمل Binding لكل الـ Callback functions.
- الألوان في الـ `glClearColor` هي ألوان الفضاء الخلفية.
- النجوم بتاخد سرعات عشوائية من 1 إلى 3.

> [!TIP]
> 
> ترتيب أوامر الـ Setup في الـ `main` مهم، مينفعش تعمل `glutCreateWindow` قبل `glutInit`.

### Definitions

- Double Buffering (`GLUT_DOUBLE`):
	تقنية بترسم المشهد بالكامل في مساحة خلفية مخفية (Back Buffer) وبعدين تبدله مع المساحة الظاهرة (Front Buffer) فجأة علشان الشاشة مترمش (Flickering).
- Callback Function:
	دالة بتسلمها لـ System علشان ينفذها هو تلقائياً لما يحصل Event معين زي ضغطة زرار أو فريم جديد.
- Parallax Effect:
	تأثير بصري بيتحقق لما الأجسام القريبة تتحرك أسرع من الأجسام البعيدة في الخلفية.
### Rules / Laws / Principles

- Main Loop Rule
- لازم `()glutMainLoop` تكون آخر حاجة في دالة `main`.
- أي كود بعداا مش هيتنفذ لحد ما البرنامج يقفل.
### Step-by-Step Process

1. تهيئة الـ GLUT وإعدادات الشاشة.  
2. تحديد الـ Display Mode (Double, RGB, Alpha).
3. تحديد الحجم وإنشاء الويندو.
4. تهيئة بيانات اللعبة زي النجوم.
5. ربط كل دوال الأحداث (Callbacks).
6. الدخول في الـ Main Loop.

### Common Mistakes / Traps

- نسيان إضافة `GLUT_DOUBLE` واستخدام Single Buffer هيخلي الرسم يبان بيترعش ويقطع مع الأنيميشن السريعة.

> [!WARNING]
> 
> استدعاء `glutDisplayFunc` مرتين بيلغي الأولانية وبيعتمد على آخر واحدة اتعملها استدعاء.

### High-Risk Exam Content

- ما هي الـ Flags المطلوبة لدعم الرسم نصف الشفاف ومنع الرمش؟ الإجابة `GLUT_DOUBLE | GLUT_RGB | GLUT_ALPHA`.
- الدالة المسؤولة عن تحديد لون خلفية المشهد هي `glClearColor` وليست `glClear`.
### Exam-Style Questions

>[!CAUTION] 
>**Q1 :**
>Which function call enters the GLUT event processing loop?

>[!IMPORTANT]
>**Answer :**
>`glutMainLoop()`.

>[!CAUTION]
>**Q2 :**
>How is the background color of the OpenGL window set, and what color is it set to?

>[!IMPORTANT]
>**Answer :**
>By using `glClearColor(0.01f, 0.02f, 0.05f, 1.0f)`, which sets it to a very dark navy blue/black.

---
# Extracted Rules & Laws

- **Array Size Rule**: All keyboard input state arrays (`keys`, `specialKeys`) must strictly have a size of 256.

- **Primitive Selection Rule**: Use `GL_POLYGON` for filled shapes and `GL_LINE_LOOP` for wireframe outlines.

- **Blending Enable/Disable Rule**: Operations utilizing alpha transparency require `glEnable(GL_BLEND)` before rendering and `glDisable(GL_BLEND)` immediately after.

- **Push and Pop Pairing Rule**: Every `glPushMatrix()` operation MUST be balanced with a corresponding `glPopMatrix()` to maintain matrix stack integrity.
  
- **Scale Limit Rule**: An object's scaling factor must be strictly constrained (e.g., `> 0.2f`) to prevent inversion or zero-scale rendering errors.
  
- **Main Loop Rule**: `glutMainLoop()` must be the final execution step in the `main` function as it enters an infinite blocking loop.

# Extracted Formulas

- **Angle to Radian**: $$rad = angle * (PI / 180.0f)$$

- **Circle Vertex (X)**: $$x = radius * cosf(theta) + cx$$

- **Circle Vertex (Y)**: $$y = radius * sinf(theta) + cy$$

- **Flicker Amplitude**: $$flicker = sinf(flameTime) * 10.0f$$

- **Vector Length (Magnitude)**:$$len = sqrtf(dirX * dirX + dirY * dirY)$$

- **Laser Direction Angle**: $$laserAngle = atan2f(dirY, dirX) * 180.0f / PI - 90.0f$$

# Study IMPORTANTs

- الـ `vector` مستخدم للـ Lasers علشان عددام متغير، لكن الـ Array للنجوم علشان عددام ثابت (200).

- الـ Rendering بيعتمد على تحريك الـ Coordinates الخاصة بالكاميرا أو الموديل باستخدام `glTranslatef` وغيرها بدلاً من تغيير نقاط الشكل الأصلية (دا بيخلي الكود أنضف).

- إدارة الكيبورد بطريقة الـ Flags بتقدم حركة ناعمة جداً في الجيمز عكس الـ Input العادي اللي بيعتمد على حدث الضغطة المنفردة واللي بيعمل توقف بسيط في البداية.

# Master Summary

- الـ Code بيبني Interactive 2D Spaceship بيتحرك بالأسهم ويدور ويسكيل ويضرب ليزر.
  
- الواجهة مرسومة بالـ Blending والـ Shapes الأساسية من غير أي Textures خارجية.
  
- الحركة بتتم عن طريق Matrix Transformations بتتحط في الـ ModelView stack لكل frame.
  
- الـ Physics بتاعة الضرب بتستخدم Trigonometry لتحديد الـ Local position وتحويله لـ Global وإطلاق الليزر في الاتجاه الصح
  .
- الـ Game Loop مبنية على `glutTimerFunc` بتستدعي نفسها كل 30ms وتطلب إعادة الرسم.

# Exam IMPORTANTs

- Examiner focus:
	غالباً بيسأل في الـ Matrix transformations ترتيبها إيه في الكود (Translate, Rotate, Scale) وتأثيرها على الشكل.
- Question patterns:
	المقارنة بين `GL_POLYGON` و `GL_QUADS` ومتى يتم استخدام كل منهم.
- High-yield facts:
	 الفرق بين `glClear` اللي بتمسح بجد و `glClearColor` اللي بتحدد لون المسح. وأهمية `gluOrtho2D`.

# Concept Connections

- الـ `shearMatrix` المخصصة مربوطة بقيمة `shearX` اللي بتتغير بحروف الـ Q والـ E، ودا بيغير في شكل الـ Transform النهائي بجانب الـ Scale والـ Rotation اللي هما ليهم دوال جاهزة في OpenGL، فدا بيوضح إن أي Transformation جاهز أو Custom بينتهي كـ 4x4 Matrix.

- استخدام `std::stringstream` مع `drawText` بيحل مشكلة إن OpenGL ملوش طريقة سهلة يرسم بيها الـ Dynamic Numbers، فبيحولها لـ String ثابت الحروف تترسم حرف حرف.

# Glossary

- **GLUT**: OpenGL Utility Toolkit (Framework for managing windows and events).

- **GL_POLYGON**: OpenGL primitive for drawing a solid filled polygon.

- **GL_QUADS**: OpenGL primitive for drawing four-sided polygons.

- **glBlendFunc**: Function to specify pixel arithmetic for transparency.

- **gluOrtho2D**: Defines a 2D orthographic projection matrix.

- **glPushMatrix**: Pushes the current matrix onto the stack.

- **glPopMatrix**: Pops the top matrix off the stack.
    
- **atan2f**: Arc tangent function handling signs correctly to place the angle in the correct quadrant.

- **std::stringstream**: Stream class to operate on strings.

---

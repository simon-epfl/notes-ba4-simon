Sam a écrit ces notes.
## 1. Styles d'interaction

You can **ask the system a question**, give it **commands**, provide **information**, or even move if it’s a **robot**.

Various **input devices** allow interaction:

- **Common inputs**: Keyboard, mouse, microphone, 2D & 3D mice.
- **Advanced inputs**: Cameras, **eye trackers**, and apps that **track physical activities** (e.g., heartbeat, distance walked).
- **Tangible interfaces**: Interacting with a system by manipulating **physical objects** instead of using a keyboard or touchscreen.

>[!Tangible Interface]
>- A system for **training logistics apprentices**.
>- Trainees **physically build a warehouse layout** using **plastic shelves** instead of using a mouse or keyboard.
>- The system **tracks** their placements with **QR codes** and a **camera**, then **simulates warehouse operations** (e.g., forklifts moving goods).
>- The goal is to **teach logistics optimization** in a hands-on, interactive way.

#### Output Devices & Immersive Interfaces

- **Standard output devices**: Screens, projectors, VR headsets.
- **Less common interfaces**:
    - **CAVE systems**: 3D spaces where images are projected onto walls, creating a fully immersive environment (without wearing a VR headset).
    - **Ambient interfaces**: Moving beyond screens and using **peripheral vision** to display information.
        - Example: A **table with embedded microphones** that detects and responds to voices.
        - Example: **Walls displaying information dynamically**, interacting with users based on their surroundings.

#### GUI

| Benefits                                                                                                                                                               | Limitations                                                                                                                       |
| ---------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------- |
| - Fewer errors compared to command-line interfaces.<br>- Users don’t have to remember exact command names (e.g., "return" vs. "retour").<br>- Learning curve is lower. | - **Nested menus** can be annoying.<br>- **Some tasks are slower** than using shortcuts (e.g., repetitive drag-and-drop actions). |

#### Types of Interfaces

- Direct manipulation: Evolved from the mouse and keyboard to touchscreens, interactive tables, and gestures.
- Forms & Input Fields:
    - Not visually appealing, but very efficient.
    - Advantages:
        - Pre-formatting avoids confusion (e.g., date formats: "12/02" vs. "02.12").
        - Auto-completion speeds up input.
        - Error handling prevents invalid entries (e.g., birth year 1322 is impossible).
        - Guides the user through a sequence (unlike a free-form UI where users may not know where to start).
    - Ideal for routine tasks (e.g., buying tickets) - but not suitable for creative tasks (e.g., designing a UI inside a form).

#### Choosing the Best Interface

No single interface is best for all users.

>[!Buying train tickets]
> An experienced railway employee benefits from structured forms because they know the system well. A tourist unfamiliar with the area might find drag-and-drop or an interactive map easier. However, users unfamiliar with geography may struggle with maps (e.g., taking too long to find Lucerne).

- The ideal interface depends on:
    - The task: Is it routine or creative?
    - The user: Are they a beginner or an expert?
- The balance between required skills and usage frequency helps determine the best UI approach.

### Three Levels of User Knowledge in UI Design

1. **Task-Specific Semantic Knowledge**
    - Independent of the UI—general domain knowledge.
    - Example: Understanding what a **table of contents** is in a text document.

2. **Computational Semantic Knowledge**
    - How a task is transformed by digital tools.
    - Example: **Paragraph styles** in word processors:
        - In the past, users **manually** added spaces between paragraphs.
        - Modern software allows **paragraph objects** with **adjustable spacing settings**.

3. **Syntactic Knowledge** (Arbitrary Design Choices):
    - Interface design choices that **users memorize** over time.
    - Example: **Copy (Ctrl+C) & Paste (Ctrl+V)**:
        - Why is **Ctrl+V for paste** instead of **Ctrl+P**?
        - It’s an **arbitrary** decision made by designers and later **standardized**.

>[!summary]
>- **GUIs improved usability** but introduced **limitations** (e.g., nested menus, slow operations).
>- **Different interfaces** suit different users **depending on their expertise and the task type**.
>- **User knowledge influences UI design**:
>	- Some knowledge comes from **real-world concepts**.
>	- Some is **unique to digital interfaces**.
>	- Some is **completely arbitrary but widely adopted** (e.g., keyboard shortcuts).
>	
Ultimately, **interface design must balance usability, efficiency, and user expectations**.


## 2. Pourquoi les utilisateurs commettent ils des erreurs?

### Types of Memory

1. **Sensory Memory**: Brief retention of visual and auditory stimuli.
2. **Working Memory**: Limited in both **time (20-30 seconds)** and **capacity (about 5-7 items)**. This is where immediate processing happens.
3. **Long-Term Memory**: A vast and **semantic** network of concepts, allowing us to make logical connections and retrieve knowledge efficiently.

### Cognitive Load and Mistakes

- **People make errors** because working memory has a limited capacity.
- Long-term memory stores everything we know, but **we can only activate a small portion at a time**.
- When cognitive load increases (e.g., multitasking, processing complex information), mistakes occur.

>[!example]
>- **Eye-tracking (pupil dilation)** and **heart rate** are used to measure cognitive load.
>- **NASA-TLX** is a widely used subjective questionnaire to assess mental workload.
>- **Dual-task experiments** (e.g., solving math problems while identifying words) show how increased difficulty in one task can spill over into another, leading to errors.

Despite working memory limits, we **perform complex tasks** by using structured information, habits, and automation. For example, driving a car involves multiple simultaneous actions (steering, shifting gears, talking), but experience and automation help manage the load.

>[!Summary]
>- Working memory is a **bottleneck** in cognition.
>- Mistakes happen when cognitive load exceeds capacity.
>- Understanding memory limitations helps design better **learning strategies, user interfaces, and work environments**.


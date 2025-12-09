# MonoLin – Altium Schematic Library Guidelines

MonoLin is a unified schematic library style designed to keep all Altium projects clean, readable, consistent, and print-friendly.  
This document defines the styling rules, design philosophy, installation steps, and usage recommendations.

---

## 🎯 Objectives

- Create clean, simple, and highly readable schematic symbols  
- Ensure consistent style across all projects  
- Provide a fully print-friendly schematic layout (A4, B/W friendly)  
- Standardize symbol sizes, grids, fonts, and colors  
- Support long-term maintainability and team collaboration  

---

## 🎨 Design Style Rules

### 1. Fonts
| Item | Size |
|------|------|
| Designators | **10** |
| Component Names | **10** |
| Parameters / Notes | 10 / 8 / 6 (only when needed) |

**Font must always be Arial.**

---

### 2. Pin Colors

#### Power Pins  
(VCC, VDD, VSS, VREF, VBUS, V+, etc.)

Use **Red-255** (NOT Altium default power-port red):

#### Signal & Ground Pins  
- Black

---

### 3. Pin Length
- Standard length: **200 mil**

Tiny packages may use shorter pins only if required.

---

### 4. Pin Style
- Border: **Small**  
- Line Width: **Smallest**

---

### 5. Symbol Colors
To keep schematics clean and print-friendly:

- Symbol lines: **Black**  
- Text: **Black**  
- Power Pins: **Red-255**  
- No extra colors anywhere

---

## 📐 Schematic Sheet Rules

### Sheet Size
- Always **A4**

### Layout Style
- One functional block per sheet (“island style”)  
- One main sheet containing global connections and project overview  
- Avoid placing multiple unrelated circuits in one sheet  

---

## 📏 Grids

### Library Grid
- Snap Grid: **100 mil**  
- Electrical Grid: **100 mil**

### Schematic Grid
- Snap Grid: **100 mil**

Reason: ensures alignment, readability, and professional appearance.

---

## ⚫ Wire Colors (Recommended)

We recommend changing all schematic wires from Altium’s default blue to **black**:

- Cleaner appearance  
- More standard in industry  
- Better print output  

*(Optional but highly recommended.)*

---

## 📦 Installation

1. Clone or download the MonoLin repository.
2. Open Altium Designer.
3. Navigate to:  
   **Preferences → Data Management → Libraries**
4. Select **Installed → Install**
5. Add:
   - `MonoLin.SchLib`

Done.

---

## 🚀 How to Use MonoLin Library

1. Set project schematic grid to **100 mil**  
2. Insert symbols from MonoLin library  
3. Follow the required styling rules:
   - Use A4 sheets  
   - Keep only one functional block per sheet  
   - Use Black wires (recommended)  
   - Use Red-255 only for power pins  
   - Keep all pins aligned to the 100-mil grid  
   - Keep symbol sizes consistent  

---

## 🧭 Design Philosophy

MonoLin aims for:

- Maximum clarity  
- Minimal visual noise  
- Full black-and-white printing compatibility  
- Professional appearance  
- Industry-standard schematic readability  
- Consistent results across long-term and multi-designer projects  

Simple, clean, and engineering-focused.

---

## 📄 License



---

## ✔ Additional Recommendations

- Keep line widths minimal  
- Avoid decorative graphics  
- Keep symbols functional and standard  
- Maintain consistent naming style  
- Avoid blue wires — black is preferred for print clarity  

---






#pragma once

#include "Header1.h"
#include "Header2.h"
#include <math.h>

namespace CppCLRWinFormsProject {

  using namespace System;
  using namespace System::ComponentModel;
  using namespace System::Collections;
  using namespace System::Windows::Forms;
  using namespace System::Data;
  using namespace System::Drawing;

  
  public ref class Form1 : public System::Windows::Forms::Form
  {
  public:
    Form1(void)
    {
      InitializeComponent();
      //
      //TODO: Add the constructor code here
      //

      // uncomment to execute the rk1-utils:
      //    N_rk1_Utils_demo::execute(); // shows how the rk1-utils can be used

    }

  protected:
    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    ~Form1()
    {
      if (components)
      {
        delete components;
      }
    }
  private: System::ComponentModel::IContainer^ components;
  protected:





  protected:

  private:
    

  private:
      int systemCounter = 0;
      double pointX = 0;
      double pointY = 0;
      double angle = 1.57;
      double speed = 0;
      double angleInterval = 0;
      double timeInterval = 0.1;

  private: System::Windows::Forms::Timer^ Timer;
  private: System::Windows::Forms::Button^ Up;
  private: System::Windows::Forms::Button^ Stop;
  private: System::Windows::Forms::Button^ Down;
  private: System::Windows::Forms::Button^ Left;
  private: System::Windows::Forms::Button^ Right;
         

      void flushTank(void) {
          pointX += speed * cos(angle) * timeInterval;
          pointY += speed * sin(angle) * timeInterval;
          angle += angleInterval * timeInterval;
      }

      void plotTank(void) {
          // e1 is plot, and clear to nothing but bg color lightblue
          Graphics^ e1 = this->CreateGraphics();
          e1->Clear(Color::LightBlue);
          // create pen setting color and width
          Pen^ pen_B = gcnew Pen(Color::LightPink, 3);

          int radius = 40;
          int initialX = 200, initialY = 500;
          int x = pointX, y = pointY;


          e1->DrawEllipse(pen_B, initialX + x - radius / 2, initialY - y - radius / 2,
              radius, radius);
          int dirX = 30 * cos(angle);
          int dirY = 30 * sin(angle);
          e1->DrawLine(pen_B, initialX + x, initialY - y, initialX + x + dirX
              , initialY - y - dirY);

      }

#pragma region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    void InitializeComponent(void)
    {
        this->components = (gcnew System::ComponentModel::Container());
        this->Timer = (gcnew System::Windows::Forms::Timer(this->components));
        this->Up = (gcnew System::Windows::Forms::Button());
        this->Stop = (gcnew System::Windows::Forms::Button());
        this->Down = (gcnew System::Windows::Forms::Button());
        this->Left = (gcnew System::Windows::Forms::Button());
        this->Right = (gcnew System::Windows::Forms::Button());
        this->SuspendLayout();
        // 
        // Timer
        // 
        this->Timer->Enabled = true;
        this->Timer->Tick += gcnew System::EventHandler(this, &Form1::Timer_Tick);
        // 
        // Up
        // 
        this->Up->Location = System::Drawing::Point(764, 43);
        this->Up->Name = L"Up";
        this->Up->Size = System::Drawing::Size(100, 50);
        this->Up->TabIndex = 0;
        this->Up->Text = L"Up";
        this->Up->UseVisualStyleBackColor = true;
        this->Up->Click += gcnew System::EventHandler(this, &Form1::Up_Click);
        // 
        // Stop
        // 
        this->Stop->Location = System::Drawing::Point(764, 118);
        this->Stop->Name = L"Stop";
        this->Stop->Size = System::Drawing::Size(100, 50);
        this->Stop->TabIndex = 1;
        this->Stop->Text = L"Stop";
        this->Stop->UseVisualStyleBackColor = true;
        this->Stop->Click += gcnew System::EventHandler(this, &Form1::Stop_Click);
        // 
        // Down
        // 
        this->Down->Location = System::Drawing::Point(764, 190);
        this->Down->Name = L"Down";
        this->Down->Size = System::Drawing::Size(100, 50);
        this->Down->TabIndex = 2;
        this->Down->Text = L"Down";
        this->Down->UseVisualStyleBackColor = true;
        this->Down->Click += gcnew System::EventHandler(this, &Form1::Down_Click);
        // 
        // Left
        // 
        this->Left->Location = System::Drawing::Point(658, 118);
        this->Left->Name = L"Left";
        this->Left->Size = System::Drawing::Size(100, 50);
        this->Left->TabIndex = 3;
        this->Left->Text = L"Left";
        this->Left->UseVisualStyleBackColor = true;
        this->Left->Click += gcnew System::EventHandler(this, &Form1::Left_Click);
        // 
        // Right
        // 
        this->Right->Location = System::Drawing::Point(870, 118);
        this->Right->Name = L"Right";
        this->Right->Size = System::Drawing::Size(100, 50);
        this->Right->TabIndex = 4;
        this->Right->Text = L"Right";
        this->Right->UseVisualStyleBackColor = true;
        this->Right->Click += gcnew System::EventHandler(this, &Form1::Right_Click);
        // 
        // Form1
        // 
        this->AutoScaleDimensions = System::Drawing::SizeF(15, 32);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->BackColor = System::Drawing::Color::LightBlue;
        this->ClientSize = System::Drawing::Size(982, 603);
        this->Controls->Add(this->Right);
        this->Controls->Add(this->Left);
        this->Controls->Add(this->Down);
        this->Controls->Add(this->Stop);
        this->Controls->Add(this->Up);
        this->Font = (gcnew System::Drawing::Font(L"Inconsolata", 18));
        this->Margin = System::Windows::Forms::Padding(8, 6, 8, 6);
        this->Name = L"Form1";
        this->Text = L"Tank";
        this->ResumeLayout(false);

    }
#pragma endregion

   // You can call the functions at a button click. If you prefer, 
    // you can call them by clicking a menu item.

 

  private: System::Void Timer_Tick(System::Object^ sender, System::EventArgs^ e) {
      flushTank();
      plotTank();
      systemCounter++;
  }
private: System::Void Up_Click(System::Object^ sender, System::EventArgs^ e) {
    speed = 5 * 5;
    angle = 1.57;
}
private: System::Void Stop_Click(System::Object^ sender, System::EventArgs^ e) {
    speed = 0;
    
}
private: System::Void Left_Click(System::Object^ sender, System::EventArgs^ e) {
    speed = 5 * 5;
    angle = 3.14;
}
private: System::Void Down_Click(System::Object^ sender, System::EventArgs^ e) {
    speed = 5 * 5;
    angle = 3.14 + 1.57;
}
private: System::Void Right_Click(System::Object^ sender, System::EventArgs^ e) {
    speed = 5 * 5;
    angle = 0;
}
}; // end of class Form1
} // end of namespace CppCLRWinFormsProject


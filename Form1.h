#pragma once


#include "Header1.h"
#include "Header2.h"

#include "data_format.h"
#define ddf
#include "lockSystem.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>



bool tracking_enable = 0;
trackingData tk;


// variable
userData usrData;
enemyData enm[5];

weaponProfile wea;
speedInformation speedInfo;
itemProfile items[3];
double timeInterval = 0.1;
int systemCounter = 0;


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
    

  public:
      
      
      
      
      

  private: System::Windows::Forms::Timer^ Timer;
  private: System::Windows::Forms::Button^ Up;
  private: System::Windows::Forms::Button^ Stop;
  private: System::Windows::Forms::Button^ Down;
  private: System::Windows::Forms::Button^ Left;
  private: System::Windows::Forms::Panel^ panel1;
  private: System::Windows::Forms::ProgressBar^ progressBar3;
  private: System::Windows::Forms::ProgressBar^ progressBar2;
  private: System::Windows::Forms::ProgressBar^ progressBar1;
  private: System::Windows::Forms::Label^ label4;
  private: System::Windows::Forms::Label^ label3;
  private: System::Windows::Forms::Label^ label2;
  private: System::Windows::Forms::Label^ label1;
  private: System::Windows::Forms::Button^ Fire;
  private: System::Windows::Forms::Button^ Lock;

  private: System::Windows::Forms::Button^ Right;
         
   
  

      void loadProfile(void){
          FILE* pFile;
          pFile = fopen("profile.dat", "r");
          fscanf(pFile, "%s", usrData.name);
          fscanf(pFile, "%lf", &usrData.pos.pointX);
          fscanf(pFile, "%lf", &usrData.pos.pointY);
          fscanf(pFile, "%lf",
              &usrData.pos.angle);
          fscanf(pFile, "%lf", &usrData.t);
          fscanf(pFile, "%lf",
              &usrData.value.hp);
          fscanf(pFile, "%lf",
              &usrData.value.sp);

          fscanf(pFile, "%lf",
              &usrData.value.mp);
          fclose(pFile);
          
          for (int i = 0; i < 5; i++) {
              enm[i].pos.pointX = rand() % 200 - 100;
              enm[i].pos.pointY = rand() % 200 - 100;
              enm[i].V.vx = rand() % 20 - 10;
              enm[i].V.vy = rand() % 20 - 10;
              enm[i].value.hp = 20;
          }

          wea.value.hp = 10;
          wea.value.sp = 5;
          wea.range = 100;
          wea.Velocity = 50;
          wea.enable = 0;

          items[0].pos.pointX = 50;
          items[0].pos.pointY = 0;
          items[1].pos.pointX = 100;
          items[1].pos.pointY = 0;
          items[2].pos.pointX = 120;
          items[2].pos.pointY = 0;
          items[0].c = 'H';
          items[1].c = 'S';
          items[2].c = 'M';
          items[0].enable = 1;
          items[1].enable = 1;
          items[2].enable = 1;

          
      }
      void flushTank(void) {
          usrData.pos.pointX += speedInfo.speed * cos(usrData.pos.angle) * timeInterval;
          usrData.pos.pointY += speedInfo.speed * sin(usrData.pos.angle) * timeInterval;
          usrData.pos.angle += speedInfo.angleInterval * timeInterval;
          
          
          if (wea.enable == 1 && wea.counter > 0)
          {
              wea.pos.pointX = wea.pos.pointX + wea.V.vx;
              wea.pos.pointY = wea.pos.pointY + wea.V.vy;
              wea.counter--;
          }
          else
          {
              wea.enable = 0;
          }


          for (int i = 0; i < 5; i++) {
              if (enm[i].enable == 1)
              {
                  enm[i].pos.pointX = enm[i].pos.pointX + enm[i].V.vx * timeInterval;
                  enm[i].pos.pointY = enm[i].pos.pointY + enm[i].V.vy * timeInterval;
                  if (enm[i].pos.pointX > 300)
                  {
                      enm[i].pos.pointX = 0;
                  }
                  if (enm[i].pos.pointX < 0)
                  {
                      enm[i].pos.pointX = 300;
                  }
                  if (enm[i].pos.pointY > 300)
                  {
                      enm[i].pos.pointY = 0;
                  }
                  if (enm[i].pos.pointY < 0)
                  {
                      enm[i].pos.pointY = 300;
                  }
              }
          }
      }

      void plotTank(void) {
          // e1 is plot, and clear to nothing but bg color lightblue
          Graphics^ e1 = this->CreateGraphics();
          e1->Clear(Color::LightBlue);
          // create pen setting color and width
          Pen^ pen_B = gcnew Pen(Color::LightPink, 3);
          Pen^ pen_k = gcnew Pen(Color::Gray, 2);

          int radius = 40;
          int initialX = 200, initialY = 500;
          int x = usrData.pos.pointX, y = usrData.pos.pointY;


          e1->DrawEllipse(pen_B, initialX + x - radius / 2, initialY - y - radius / 2,
              radius, radius);
          int dirX = 30 * cos(usrData.pos.angle);
          int dirY = 30 * sin(usrData.pos.angle);
          e1->DrawLine(pen_B, initialX + x, initialY - y, initialX + x + dirX
              , initialY - y - dirY);

          for (int i = 0; i < 5; i++)
          {
              if (enm[i].enable == 1)
              {
                  
                  e1->DrawRectangle(pen_k, initialX + enm[i].pos.pointX, initialY - enm[i].pos.pointY, 20, 20);
              }
          }

          Pen^ pen_B5 = gcnew Pen(Color::Blue, 10);
          
          if (wea.enable == 1 && wea.counter > 0)
          {
              radius = wea.diameter;
              
              e1->DrawEllipse(pen_B5, initialX + wea.pos.pointX - radius / 2, initialY - wea.pos.pointY - radius / 2,
                  radius, radius
              );
          }

          for (int i = 0; i < 3; i++)
          {
              if (items[i].enable == 1)
              {
                  radius = items[i].diameter;
                  
                  e1->DrawEllipse(pen_B, initialX + items[i].pos.pointX - radius / 2, initialY - items[i].pos.pointY - radius / 2,
                      radius, radius);
              }
          }

          if (tracking_enable == 1)
          {
              tk = lockSystem(usrData, enm);
              usrData.pos.angle = tk.pos.angle;
          }
          usrData.pos.pointX = usrData.pos.pointX + usrData.speed.speed * cos(usrData.pos.angle) * timeInterval;
          usrData.pos.pointY = usrData.pos.pointY + usrData.speed.speed * sin(usrData.pos.angle) * timeInterval;
          usrData.pos.angle = usrData.pos.angle + usrData.speed.angleInterval * timeInterval;

          

      }

      void textDisplayer(void)
      {
          String^ str = gcnew String(usrData.name);
          this->label1->Text = str;
          this->progressBar1->Value = usrData.value.hp;
          this->label2->Text = ("HP:" + Convert::ToString(usrData.value.hp) + "/100");
          this->progressBar2->Value = usrData.value.sp;
          this->label3->Text = ("SP:" + Convert::ToString(usrData.value.sp) + "/100");
          this->progressBar3->Value = usrData.value.mp;
          this->label4->Text = ("MP:" + Convert::ToString(usrData.value.mp) + "/100");
      };

      void collsionDetection(void)
      {
          // collsion between tank and obstacles
          for (int i = 0; i < 5; i++)
          {
              float dis = sqrt((usrData.pos.pointX - enm[i].pos.pointX) * (usrData.pos.pointX -
                  enm[i].pos.pointX) + (usrData.pos.pointY - enm[i].pos.pointY) * (usrData.pos.pointY -
                      enm[i].pos.pointY));
              if (dis < enm[i].width && enm[i].enable == 1)
              {
                  usrData.value.hp -= enm[i].value.hp;
                  enm[i].enable = 0;
              }
          }

          // collsion between weapon and obstacles
          for (int i = 0; i < 5; i++)
          {
              float dis = sqrt((wea.pos.pointX - enm[i].pos.pointX) * (wea.pos.pointX - enm[i].pos.pointX) +
                  (wea.pos.pointY - enm[i].pos.pointY) * (wea.pos.pointY - enm[i].pos.pointY));
              if (dis < enm[i].width && enm[i].enable == 1 && wea.enable == 1)
              {
                  enm[i].value.hp -= wea.value.hp;
                  wea.enable = 0; // weapon disappear
                  if (enm[i].value.hp <= 0)
                  {
                      enm[i].enable = 0; // obstacle disappear
                  }
              }
          }

          for (int i = 0; i < 3; i++)
          {
              float dis = sqrt((usrData.pos.pointX - items[i].pos.pointX) * (usrData.pos.pointX - items[i].pos.pointX) + (usrData.pos.pointY -
                  items[i].pos.pointY) * (usrData.pos.pointY - items[i].pos.pointY));
              if (dis < 30 && items[i].enable == 1)
              {
                  switch (items[i].c)
                  {
                  case 'H':
                      if (usrData.value.hp < 100)
                          usrData.value.hp++;
                      break;
                  case 'S':
                      if (usrData.value.sp < 100)
                          usrData.value.sp++;
                      break;
                  case 'M':
                      if (usrData.value.mp < 100)
                          usrData.value.mp++;
                      break;
                  default:
                      break;
                  }
              }
          }
          
      

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
    this->panel1 = (gcnew System::Windows::Forms::Panel());
    this->progressBar3 = (gcnew System::Windows::Forms::ProgressBar());
    this->progressBar2 = (gcnew System::Windows::Forms::ProgressBar());
    this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
    this->label4 = (gcnew System::Windows::Forms::Label());
    this->label3 = (gcnew System::Windows::Forms::Label());
    this->label2 = (gcnew System::Windows::Forms::Label());
    this->label1 = (gcnew System::Windows::Forms::Label());
    this->Fire = (gcnew System::Windows::Forms::Button());
    this->Lock = (gcnew System::Windows::Forms::Button());
    this->panel1->SuspendLayout();
    this->SuspendLayout();
    // 
    // Timer
    // 
    this->Timer->Enabled = true;
    this->Timer->Tick += gcnew System::EventHandler(this, &Form1::Timer_Tick);
    // 
    // Up
    // 
    this->Up->Location = System::Drawing::Point(764, 12);
    this->Up->Name = L"Up";
    this->Up->Size = System::Drawing::Size(100, 50);
    this->Up->TabIndex = 0;
    this->Up->Text = L"Up";
    this->Up->UseVisualStyleBackColor = true;
    this->Up->Click += gcnew System::EventHandler(this, &Form1::Up_Click);
    // 
    // Stop
    // 
    this->Stop->Location = System::Drawing::Point(764, 78);
    this->Stop->Name = L"Stop";
    this->Stop->Size = System::Drawing::Size(100, 50);
    this->Stop->TabIndex = 1;
    this->Stop->Text = L"Stop";
    this->Stop->UseVisualStyleBackColor = true;
    this->Stop->Click += gcnew System::EventHandler(this, &Form1::Stop_Click);
    // 
    // Down
    // 
    this->Down->Location = System::Drawing::Point(764, 146);
    this->Down->Name = L"Down";
    this->Down->Size = System::Drawing::Size(100, 50);
    this->Down->TabIndex = 2;
    this->Down->Text = L"Down";
    this->Down->UseVisualStyleBackColor = true;
    this->Down->Click += gcnew System::EventHandler(this, &Form1::Down_Click);
    // 
    // Left
    // 
    this->Left->Location = System::Drawing::Point(658, 78);
    this->Left->Name = L"Left";
    this->Left->Size = System::Drawing::Size(100, 50);
    this->Left->TabIndex = 3;
    this->Left->Text = L"Left";
    this->Left->UseVisualStyleBackColor = true;
    this->Left->Click += gcnew System::EventHandler(this, &Form1::Left_Click);
    // 
    // Right
    // 
    this->Right->Location = System::Drawing::Point(870, 78);
    this->Right->Name = L"Right";
    this->Right->Size = System::Drawing::Size(100, 50);
    this->Right->TabIndex = 4;
    this->Right->Text = L"Right";
    this->Right->UseVisualStyleBackColor = true;
    this->Right->Click += gcnew System::EventHandler(this, &Form1::Right_Click);
    // 
    // panel1
    // 
    this->panel1->BackColor = System::Drawing::Color::LightCoral;
    this->panel1->Controls->Add(this->progressBar3);
    this->panel1->Controls->Add(this->progressBar2);
    this->panel1->Controls->Add(this->progressBar1);
    this->panel1->Controls->Add(this->label4);
    this->panel1->Controls->Add(this->label3);
    this->panel1->Controls->Add(this->label2);
    this->panel1->Controls->Add(this->label1);
    this->panel1->Location = System::Drawing::Point(658, 231);
    this->panel1->Name = L"panel1";
    this->panel1->Size = System::Drawing::Size(312, 350);
    this->panel1->TabIndex = 5;
    // 
    // progressBar3
    // 
    this->progressBar3->Location = System::Drawing::Point(169, 209);
    this->progressBar3->Name = L"progressBar3";
    this->progressBar3->Size = System::Drawing::Size(118, 32);
    this->progressBar3->TabIndex = 8;
    this->progressBar3->Click += gcnew System::EventHandler(this, &Form1::progressBar3_Click);
    // 
    // progressBar2
    // 
    this->progressBar2->Location = System::Drawing::Point(169, 148);
    this->progressBar2->Name = L"progressBar2";
    this->progressBar2->Size = System::Drawing::Size(118, 32);
    this->progressBar2->TabIndex = 7;
    this->progressBar2->Click += gcnew System::EventHandler(this, &Form1::progressBar2_Click);
    // 
    // progressBar1
    // 
    this->progressBar1->Location = System::Drawing::Point(169, 80);
    this->progressBar1->Name = L"progressBar1";
    this->progressBar1->Size = System::Drawing::Size(118, 32);
    this->progressBar1->TabIndex = 6;
    // 
    // label4
    // 
    this->label4->AutoSize = true;
    this->label4->Location = System::Drawing::Point(22, 209);
    this->label4->Name = L"label4";
    this->label4->Size = System::Drawing::Size(104, 32);
    this->label4->TabIndex = 3;
    this->label4->Text = L"label4";
    // 
    // label3
    // 
    this->label3->AutoSize = true;
    this->label3->Location = System::Drawing::Point(22, 148);
    this->label3->Name = L"label3";
    this->label3->Size = System::Drawing::Size(104, 32);
    this->label3->TabIndex = 2;
    this->label3->Text = L"label3";
    // 
    // label2
    // 
    this->label2->AutoSize = true;
    this->label2->Location = System::Drawing::Point(22, 80);
    this->label2->Name = L"label2";
    this->label2->Size = System::Drawing::Size(104, 32);
    this->label2->TabIndex = 1;
    this->label2->Text = L"label2";
    this->label2->Click += gcnew System::EventHandler(this, &Form1::label2_Click);
    // 
    // label1
    // 
    this->label1->AutoSize = true;
    this->label1->Location = System::Drawing::Point(22, 14);
    this->label1->Name = L"label1";
    this->label1->Size = System::Drawing::Size(104, 32);
    this->label1->TabIndex = 0;
    this->label1->Text = L"label1";
    this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
    // 
    // Fire
    // 
    this->Fire->Location = System::Drawing::Point(658, 12);
    this->Fire->Name = L"Fire";
    this->Fire->Size = System::Drawing::Size(100, 50);
    this->Fire->TabIndex = 6;
    this->Fire->Text = L"Fire";
    this->Fire->UseVisualStyleBackColor = true;
    this->Fire->Click += gcnew System::EventHandler(this, &Form1::Fire_Click);
    // 
    // Lock
    // 
    this->Lock->Font = (gcnew System::Drawing::Font(L"Inconsolata", 14));
    this->Lock->Location = System::Drawing::Point(870, 12);
    this->Lock->Name = L"Lock";
    this->Lock->Size = System::Drawing::Size(100, 50);
    this->Lock->TabIndex = 7;
    this->Lock->Text = L"Unlock";
    this->Lock->UseVisualStyleBackColor = true;
    this->Lock->Click += gcnew System::EventHandler(this, &Form1::Lock_Click);
    // 
    // Form1
    // 
    this->AutoScaleDimensions = System::Drawing::SizeF(15, 32);
    this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
    this->BackColor = System::Drawing::Color::LightBlue;
    this->ClientSize = System::Drawing::Size(982, 603);
    this->Controls->Add(this->Lock);
    this->Controls->Add(this->Fire);
    this->Controls->Add(this->panel1);
    this->Controls->Add(this->Right);
    this->Controls->Add(this->Left);
    this->Controls->Add(this->Down);
    this->Controls->Add(this->Stop);
    this->Controls->Add(this->Up);
    this->Font = (gcnew System::Drawing::Font(L"Inconsolata", 18));
    this->Margin = System::Windows::Forms::Padding(8, 6, 8, 6);
    this->Name = L"Form1";
    this->Text = L"Tank";
    this->panel1->ResumeLayout(false);
    this->panel1->PerformLayout();
    this->ResumeLayout(false);

}
#pragma endregion

// You can call the functions at a button click. If you prefer, 
 // you can call them by clicking a menu item.



  private: System::Void Timer_Tick(System::Object^ sender, System::EventArgs^ e) {
      if (systemCounter == 0) {
          loadProfile();
      }
      flushTank();
      plotTank();
      textDisplayer();
      collsionDetection();
      systemCounter++;
      
  }
private: System::Void Up_Click(System::Object^ sender, System::EventArgs^ e) {
    speedInfo.speed = 5 * 5;
    
}
private: System::Void Stop_Click(System::Object^ sender, System::EventArgs^ e) {
    speedInfo.speed = 0;
    speedInfo.angleInterval = 0;
    
    

}
private: System::Void Left_Click(System::Object^ sender, System::EventArgs^ e) {
    speedInfo.angleInterval = 0.174 * 5;
}
private: System::Void Down_Click(System::Object^ sender, System::EventArgs^ e) {
    speedInfo.speed = -5 * 5;
    
}
private: System::Void Right_Click(System::Object^ sender, System::EventArgs^ e) {
    speedInfo.angleInterval = -0.174 * 5;
}
private: System::Void progressBar3_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void progressBar2_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void Fire_Click(System::Object^ sender, System::EventArgs^ e) {

    wea.enable = 1;
    wea.pos.pointX = usrData.pos.pointX;
    wea.pos.pointY = usrData.pos.pointY;
    usrData.value.sp = usrData.value.sp - wea.value.sp;
    wea.V.vx = wea.Velocity * cos(usrData.pos.angle) * timeInterval;
    wea.V.vy = wea.Velocity * sin(usrData.pos.angle) * timeInterval;
    wea.counter = int((wea.range / wea.Velocity) * (1 / timeInterval));
}
private: System::Void Lock_Click(System::Object^ sender, System::EventArgs^ e) {

    if (tracking_enable == 0)
    {
        tracking_enable = 1;
        Lock->Text = "Lock";
    }
    else
    {
        tracking_enable = 0;
        Lock->Text = "Unlock";
    }
}


}; // end of class Form1
} // end of namespace CppCLRWinFormsProject


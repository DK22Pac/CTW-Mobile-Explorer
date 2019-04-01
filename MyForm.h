/*
/* GTA Chinatown Wars Mobile Explorer
/* https://github.com/DK22Pac/CTW-Mobile-Explorer
/* 2014-2019
*/
#pragma once
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include "CTWResources.h"
#include "dffapi\Clump.h"
#include "DffExport.h"
#include "ModelNameMap.h"
#include "TextureExport.h"
#include <list>
#include <vector>
#include "GXT.h"

char lastPakPath[512];
char lastDXTPath[512];
char lastROMPath[512];
bool pakOpened = false;
bool dxtOpened = false;
bool romOpened = false;

sRomPack romData;
sDxtPack dxtPack;
sPakArchive pakArchive;

namespace CTWMobileExplorer {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Runtime::InteropServices;

    public ref class MyForm : public System::Windows::Forms::Form {
    public:
        MyForm(void) {
            InitializeComponent();

            FILE *testFile = fopen("mapdivision.txt", "rb");
            if (testFile) {
                fclose(testFile);
                this->menuItem9->Enabled = true;
            }
            else
                this->menuItem9->Enabled = false;
            converter::init((HWND)(this->Handle.ToPointer()));
        }

    protected:
        ~MyForm() {
            delete components;
        }
    private: System::Windows::Forms::MainMenu^  mainMenu1;
    protected:
    private: System::Windows::Forms::MenuItem^  menuItem1;
    private: System::Windows::Forms::MenuItem^  menuItem2;
    private: System::Windows::Forms::MenuItem^  menuItem3;

    private: System::Windows::Forms::MenuItem^  menuItem5;
    private: System::Windows::Forms::TreeView^  treeView1;
    private: System::Windows::Forms::Button^  buttonExportBinary;

    private: System::Windows::Forms::Button^  buttonExport;
    private: System::Windows::Forms::TextBox^  textBoxResourceType;


    private: System::Windows::Forms::TextBox^  textBoxNumResources;
    private: System::Windows::Forms::TreeView^  treeViewData;
    private: System::Windows::Forms::MenuItem^  menuItem6;
    private: System::Windows::Forms::MenuItem^  menuItem7;
    private: System::Windows::Forms::MenuItem^  menuItem8;
    private: Ookii::Dialogs::VistaFolderBrowserDialog^  vistaFolderBrowserDialog1;
    private: System::Windows::Forms::MenuItem^  menuItem4;
    private: System::Windows::Forms::MenuItem^  menuItem9;
    private: System::Windows::Forms::MenuItem^  menuItem10;
    private: System::Windows::Forms::TabControl^  tabControl1;
    private: System::Windows::Forms::TabPage^  tabPage1;
    private: System::Windows::Forms::TabPage^  tabPage2;
    private: System::Windows::Forms::PictureBox^  pictureBox1;
    private: System::Windows::Forms::Panel^  panel1;
    private: System::Windows::Forms::MenuItem^  menuItem11;
    private: System::Windows::Forms::MenuItem^  menuItem12;


    private: System::ComponentModel::IContainer^  components;

    private:
    #pragma region Windows Form Designer generated code
        void InitializeComponent(void) {
            this->components = (gcnew System::ComponentModel::Container());
            System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
            this->mainMenu1 = (gcnew System::Windows::Forms::MainMenu(this->components));
            this->menuItem1 = (gcnew System::Windows::Forms::MenuItem());
            this->menuItem2 = (gcnew System::Windows::Forms::MenuItem());
            this->menuItem3 = (gcnew System::Windows::Forms::MenuItem());
            this->menuItem5 = (gcnew System::Windows::Forms::MenuItem());
            this->menuItem6 = (gcnew System::Windows::Forms::MenuItem());
            this->menuItem7 = (gcnew System::Windows::Forms::MenuItem());
            this->menuItem8 = (gcnew System::Windows::Forms::MenuItem());
            this->menuItem4 = (gcnew System::Windows::Forms::MenuItem());
            this->menuItem9 = (gcnew System::Windows::Forms::MenuItem());
            this->menuItem10 = (gcnew System::Windows::Forms::MenuItem());
            this->menuItem11 = (gcnew System::Windows::Forms::MenuItem());
            this->menuItem12 = (gcnew System::Windows::Forms::MenuItem());
            this->treeView1 = (gcnew System::Windows::Forms::TreeView());
            this->buttonExportBinary = (gcnew System::Windows::Forms::Button());
            this->buttonExport = (gcnew System::Windows::Forms::Button());
            this->textBoxResourceType = (gcnew System::Windows::Forms::TextBox());
            this->textBoxNumResources = (gcnew System::Windows::Forms::TextBox());
            this->treeViewData = (gcnew System::Windows::Forms::TreeView());
            this->vistaFolderBrowserDialog1 = (gcnew Ookii::Dialogs::VistaFolderBrowserDialog());
            this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
            this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
            this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
            this->panel1 = (gcnew System::Windows::Forms::Panel());
            this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
            this->tabControl1->SuspendLayout();
            this->tabPage1->SuspendLayout();
            this->tabPage2->SuspendLayout();
            this->panel1->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
            this->SuspendLayout();
            // 
            // mainMenu1
            // 
            this->mainMenu1->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(3) {
                this->menuItem1, this->menuItem6,
                    this->menuItem11
            });
            // 
            // menuItem1
            // 
            this->menuItem1->Index = 0;
            this->menuItem1->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(3) {
                this->menuItem2, this->menuItem3,
                    this->menuItem5
            });
            this->menuItem1->Text = L"File";
            // 
            // menuItem2
            // 
            this->menuItem2->Index = 0;
            this->menuItem2->Text = L"Open GAME.PAK";
            this->menuItem2->Click += gcnew System::EventHandler(this, &MyForm::menuItem2_Click);
            // 
            // menuItem3
            // 
            this->menuItem3->Index = 1;
            this->menuItem3->Text = L"Open ROM.WAD";
            this->menuItem3->Click += gcnew System::EventHandler(this, &MyForm::menuItem3_Click);
            // 
            // menuItem5
            // 
            this->menuItem5->Index = 2;
            this->menuItem5->Text = L"Open DXT.BIN";
            this->menuItem5->Click += gcnew System::EventHandler(this, &MyForm::menuItem5_Click);
            // 
            // menuItem6
            // 
            this->menuItem6->Index = 1;
            this->menuItem6->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(5) {
                this->menuItem7, this->menuItem8,
                    this->menuItem4, this->menuItem9, this->menuItem10
            });
            this->menuItem6->Text = L"Export";
            // 
            // menuItem7
            // 
            this->menuItem7->Index = 0;
            this->menuItem7->Text = L"Export all textures";
            this->menuItem7->Click += gcnew System::EventHandler(this, &MyForm::menuItem7_Click);
            // 
            // menuItem8
            // 
            this->menuItem8->Index = 1;
            this->menuItem8->Text = L"Export all models";
            this->menuItem8->Click += gcnew System::EventHandler(this, &MyForm::menuItem8_Click);
            // 
            // menuItem4
            // 
            this->menuItem4->Index = 2;
            this->menuItem4->Text = L"Export all models (single)";
            this->menuItem4->Click += gcnew System::EventHandler(this, &MyForm::menuItem4_Click);
            // 
            // menuItem9
            // 
            this->menuItem9->Index = 3;
            this->menuItem9->Text = L"Generate map (with mapdivision.txt)";
            this->menuItem9->Click += gcnew System::EventHandler(this, &MyForm::menuItem9_Click);
            // 
            // menuItem10
            // 
            this->menuItem10->Index = 4;
            this->menuItem10->Text = L"Export sectors data";
            this->menuItem10->Click += gcnew System::EventHandler(this, &MyForm::menuItem10_Click);
            // 
            // menuItem11
            // 
            this->menuItem11->Index = 2;
            this->menuItem11->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(1) { this->menuItem12 });
            this->menuItem11->Text = L"Preview";
            // 
            // menuItem12
            // 
            this->menuItem12->Index = 0;
            this->menuItem12->Text = L"Background";
            this->menuItem12->Click += gcnew System::EventHandler(this, &MyForm::menuItem12_Click);
            // 
            // treeView1
            // 
            this->treeView1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->treeView1->Location = System::Drawing::Point(13, 75);
            this->treeView1->Name = L"treeView1";
            this->treeView1->Size = System::Drawing::Size(369, 544);
            this->treeView1->TabIndex = 0;
            this->treeView1->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MyForm::treeView1_AfterSelect);
            // 
            // buttonExportBinary
            // 
            this->buttonExportBinary->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->buttonExportBinary->Location = System::Drawing::Point(402, 46);
            this->buttonExportBinary->Name = L"buttonExportBinary";
            this->buttonExportBinary->Size = System::Drawing::Size(228, 43);
            this->buttonExportBinary->TabIndex = 1;
            this->buttonExportBinary->Text = L"Export Binary Data";
            this->buttonExportBinary->UseVisualStyleBackColor = true;
            this->buttonExportBinary->Click += gcnew System::EventHandler(this, &MyForm::buttonExportBinary_Click);
            // 
            // buttonExport
            // 
            this->buttonExport->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->buttonExport->Location = System::Drawing::Point(651, 46);
            this->buttonExport->Name = L"buttonExport";
            this->buttonExport->Size = System::Drawing::Size(254, 53);
            this->buttonExport->TabIndex = 2;
            this->buttonExport->Text = L"Export to DFF";
            this->buttonExport->UseVisualStyleBackColor = true;
            this->buttonExport->Visible = false;
            this->buttonExport->Click += gcnew System::EventHandler(this, &MyForm::buttonExport_Click);
            // 
            // textBoxResourceType
            // 
            this->textBoxResourceType->BackColor = System::Drawing::SystemColors::Control;
            this->textBoxResourceType->BorderStyle = System::Windows::Forms::BorderStyle::None;
            this->textBoxResourceType->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular,
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
            this->textBoxResourceType->Location = System::Drawing::Point(526, 12);
            this->textBoxResourceType->Name = L"textBoxResourceType";
            this->textBoxResourceType->Size = System::Drawing::Size(254, 28);
            this->textBoxResourceType->TabIndex = 3;
            this->textBoxResourceType->Text = L"Model Resource";
            this->textBoxResourceType->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
            this->textBoxResourceType->Visible = false;
            // 
            // textBoxNumResources
            // 
            this->textBoxNumResources->BackColor = System::Drawing::SystemColors::Control;
            this->textBoxNumResources->BorderStyle = System::Windows::Forms::BorderStyle::None;
            this->textBoxNumResources->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Regular,
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
            this->textBoxNumResources->Location = System::Drawing::Point(23, 12);
            this->textBoxNumResources->Name = L"textBoxNumResources";
            this->textBoxNumResources->Size = System::Drawing::Size(359, 55);
            this->textBoxNumResources->TabIndex = 4;
            // 
            // treeViewData
            // 
            this->treeViewData->BackColor = System::Drawing::SystemColors::Window;
            this->treeViewData->BorderStyle = System::Windows::Forms::BorderStyle::None;
            this->treeViewData->Location = System::Drawing::Point(6, 6);
            this->treeViewData->Name = L"treeViewData";
            this->treeViewData->Size = System::Drawing::Size(494, 474);
            this->treeViewData->TabIndex = 5;
            this->treeViewData->Visible = false;
            this->treeViewData->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MyForm::treeView2_AfterSelect);
            // 
            // tabControl1
            // 
            this->tabControl1->Controls->Add(this->tabPage1);
            this->tabControl1->Controls->Add(this->tabPage2);
            this->tabControl1->Location = System::Drawing::Point(398, 105);
            this->tabControl1->Name = L"tabControl1";
            this->tabControl1->SelectedIndex = 0;
            this->tabControl1->Size = System::Drawing::Size(514, 512);
            this->tabControl1->TabIndex = 6;
            // 
            // tabPage1
            // 
            this->tabPage1->Controls->Add(this->treeViewData);
            this->tabPage1->Location = System::Drawing::Point(4, 22);
            this->tabPage1->Name = L"tabPage1";
            this->tabPage1->Padding = System::Windows::Forms::Padding(3);
            this->tabPage1->Size = System::Drawing::Size(506, 486);
            this->tabPage1->TabIndex = 0;
            this->tabPage1->Text = L"Structure";
            this->tabPage1->UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this->tabPage2->Controls->Add(this->panel1);
            this->tabPage2->Location = System::Drawing::Point(4, 22);
            this->tabPage2->Name = L"tabPage2";
            this->tabPage2->Padding = System::Windows::Forms::Padding(3);
            this->tabPage2->Size = System::Drawing::Size(506, 486);
            this->tabPage2->TabIndex = 1;
            this->tabPage2->Text = L"Preview";
            this->tabPage2->UseVisualStyleBackColor = true;
            // 
            // panel1
            // 
            this->panel1->AutoScroll = true;
            this->panel1->BackColor = System::Drawing::Color::Transparent;
            this->panel1->Controls->Add(this->pictureBox1);
            this->panel1->Location = System::Drawing::Point(0, 0);
            this->panel1->Margin = System::Windows::Forms::Padding(0);
            this->panel1->Name = L"panel1";
            this->panel1->Size = System::Drawing::Size(503, 485);
            this->panel1->TabIndex = 1;
            // 
            // pictureBox1
            // 
            this->pictureBox1->Location = System::Drawing::Point(0, 3);
            this->pictureBox1->Name = L"pictureBox1";
            this->pictureBox1->Size = System::Drawing::Size(475, 450);
            this->pictureBox1->TabIndex = 0;
            this->pictureBox1->TabStop = false;
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(924, 629);
            this->Controls->Add(this->tabControl1);
            this->Controls->Add(this->textBoxNumResources);
            this->Controls->Add(this->textBoxResourceType);
            this->Controls->Add(this->buttonExport);
            this->Controls->Add(this->buttonExportBinary);
            this->Controls->Add(this->treeView1);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
            this->MaximizeBox = false;
            this->Menu = this->mainMenu1;
            this->Name = L"MyForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"CTW-Explorer";
            this->tabControl1->ResumeLayout(false);
            this->tabPage1->ResumeLayout(false);
            this->tabPage2->ResumeLayout(false);
            this->panel1->ResumeLayout(false);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
    #pragma endregion
    private:
        System::Void menuItem2_Click(System::Object^  sender, System::EventArgs^  e) {
            OpenFileDialog^ dlg = gcnew OpenFileDialog();
            dlg->Filter = "GTA Chinatown Wars Game Package|*.pak";
            if (dlg->ShowDialog() == Windows::Forms::DialogResult::OK) {
                this->textBoxResourceType->Text = "";
                this->buttonExport->Visible = false;
                this->treeViewData->Nodes->Clear();
                this->treeView1->Nodes->Clear();
                this->textBoxNumResources->Text = "";
                this->treeViewData->Visible = false;
                this->pictureBox1->Visible = false;
                this->tabPage2->Visible = false;
                modelNames.clear();
                if (pakArchive.pResourceOffsets) {
                    delete[] pakArchive.pResourceOffsets;
                    pakArchive.pResourceOffsets = NULL;
                }
                strcpy(lastPakPath, (char*)(void*)Marshal::StringToHGlobalAnsi(dlg->FileName));
                FILE *file = fopen(lastPakPath, "rb");
                if (!file)
                    return;
                fseek(file, 0, SEEK_END);
                pakArchive.fileSize = ftell(file);
                fseek(file, 0, SEEK_SET);
                fread(&pakArchive, 24, 1, file);
                pakArchive.pResourceOffsets = new unsigned short[pakArchive.resourcesCount];
                fread(pakArchive.pResourceOffsets, 2, 2036, file);
                fseek(file, pakArchive.resourceBlocksCount * 4096, SEEK_SET);
                fread(&pakArchive.pResourceOffsets[2036], 2, pakArchive.resourcesCount - 2036, file);
                char text[128];
                sprintf(text, "%d resources", pakArchive.resourcesCount);
                this->textBoxNumResources->Text = gcnew String(text);

                pakArchive.MapResourceNames(file);

                for (int i = 0; i < pakArchive.resourcesCount; i++) {
                    char name[64];
                    if (modelNames.getName(i))
                        strcpy(name, modelNames.getName(i));
                    else {
                        switch (pakArchive.GetResourceType(i, file)) {
                        case RESOURCE_TEXTURE:
                            sprintf(name, "texture%d.tex", i);
                            break;
                        case RESOURCE_MODEL:
                            sprintf(name, "model%d.mdl", i);
                            break;
                        default:
                            sprintf(name, "resource%d.res", i);
                            break;
                        }
                    }
                    char resinfo[32];
                    sprintf(resinfo, " (id %d @ 0x%X)", i, pakArchive.getResourceOffset(i));
                    strcat(name, resinfo);
                    TreeNode ^node = this->treeView1->Nodes->Add(gcnew String(name));
                    if (strstr(name, ".wbl")) {
                        this->treeViewData->Visible = true;
                        fseek(file, pakArchive.getResourceOffset(i), SEEK_SET);
                        WorldSector wrldSector;
                        fread(&wrldSector, 40, 1, file);
                        std::list<unsigned int> meshOffsets;
                        for (int s = 0; s < 4; s++) {
                            fseek(file, pakArchive.getResourceOffset(i) + 40 + wrldSector.sectorOffsets[s], SEEK_SET);
                            Sector sector;
                            fread(&sector, 12, 1, file);
                            for (int l = 0; l < sector.numLevels; l++) {
                                SectorLevel level;
                                fread(&level, 16, 1, file);
                            }
                            for (int i = 0; i < sector.numInstances; i++) {
                                ModelInstance instance;
                                fread(&instance, 16, 1, file);
                                bool found = false;
                                for (auto m = meshOffsets.begin(); m != meshOffsets.end(); m++) {
                                    if (*m == instance.offsetToMesh) {
                                        found = true;
                                        break;
                                    }
                                }
                                if (!found)
                                    meshOffsets.push_back(instance.offsetToMesh);
                            }
                        }
                        unsigned int counter = 0;
                        for (auto m = meshOffsets.begin(); m != meshOffsets.end(); m++) {
                            sprintf(text, "worldmodel%d_%d.mdl (id %d @ 0x%X)", i, counter, counter,
                                pakArchive.getResourceOffset(i) + *m);
                            node->Nodes->Add(gcnew String(text));
                            counter++;
                        }
                    }
                }
                fclose(file);
                dxtOpened = false;
                pakOpened = true;
                romOpened = false;
                this->Text = "CTW-Explorer - game.pak";
            }
        }
    private:
        System::Void treeView1_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
            unsigned int id, type, offset;
            char name[64];
            char text[64];
            char fmt[64];
            FILE *pak;
            ResourceModelHeader modelHeader;
            ResourceTextureHeader texHeader;
            ModelVertex *verts = NULL;
            ModelMatrix *matrices = NULL;
            ModelMaterial *materials = NULL;
            TreeNode ^verticesNode;
            TreeNode ^vertexNode;
            TreeNode ^materialsNode;
            TreeNode ^matNode;
            TreeNode ^matricesNode;
            TreeNode ^matrixNode;
            pakArchive.NodeGetInfo((char*)(void*)Marshal::StringToHGlobalAnsi(this->treeView1->SelectedNode->Text),
                &id, &type, &offset, name);
            this->pictureBox1->Visible = false;
            this->tabPage2->Visible = false;
            if (type == RESOURCE_TEXTURE) {
                this->textBoxResourceType->Text = "Texture Resource";
                this->buttonExport->Text = "Export to PNG";
                this->buttonExport->Visible = true;
                this->treeViewData->Nodes->Clear();
                this->treeViewData->Visible = true;
            
                this->tabControl1->SelectedIndex = 1;
            
                char *pixels;
                unsigned int w, h;
                bool hasAlpha;
            
                if (pakOpened) {
                    pak = fopen(lastPakPath, "rb");
                    fseek(pak, pakArchive.getResourceOffset(id), SEEK_SET);
                    fread(&texHeader, 12, 1, pak);
                    fseek(pak, pakArchive.getResourceOffset(id), SEEK_SET);
                    GetTexturePixels(pak, pakArchive.getResourceSize(id), &pixels, &w, &h, &hasAlpha);
                    fclose(pak);
                }
                else {
                    pak = fopen(lastDXTPath, "rb");
                    fseek(pak, dxtPack.offsets[id], SEEK_SET);
                    fread(&texHeader, 12, 1, pak);
                    fseek(pak, dxtPack.offsets[id], SEEK_SET);
                    GetTexturePixels(pak, dxtPack.sizes[id], &pixels, &w, &h, &hasAlpha);
                    fclose(pak);
                }
            
                sprintf(text, "Width:  %d", texHeader.width);
                this->treeViewData->Nodes->Add(gcnew String(text));
                sprintf(text, "Height: %d", texHeader.height);
                this->treeViewData->Nodes->Add(gcnew String(text));
                GetTextureFormatName(texHeader.format, fmt);
                sprintf(text, "Format: %s", fmt);
                this->treeViewData->Nodes->Add(gcnew String(text));
                sprintf(text, "Depth: %d", texHeader.depth);
                this->treeViewData->Nodes->Add(gcnew String(text));
                sprintf(text, "Has Alpha: %d", texHeader.hasAlpha);
                this->treeViewData->Nodes->Add(gcnew String(text));
                sprintf(text, "PixelsSize: %d", texHeader.pixelsSize);
                this->treeViewData->Nodes->Add(gcnew String(text));
                sprintf(text, "Pixels (%d bytes)", texHeader.pixelsSize);
                this->treeViewData->Nodes->Add(gcnew String(text));
            
                this->buttonExport->Enabled = true;
            
                this->pictureBox1->Visible = true;
                this->tabPage2->Visible = true;
                Bitmap ^b = gcnew Bitmap(w, h);
                _abgr *pPixel = (_abgr *)pixels;
                for (int y = 0; y < h; y++) {
                    for (int x = 0; x < w; x++) {
                        if (hasAlpha)
                            b->SetPixel(x, y, Color::FromArgb(pPixel->a, pPixel->r, pPixel->g, pPixel->b));
                        else
                            b->SetPixel(x, y, Color::FromArgb(pPixel->r, pPixel->g, pPixel->b));
                        pPixel++;
                    }
                }
                delete[] pixels;
                this->pictureBox1->BackgroundImage = b;
                this->pictureBox1->Size = b->Size;
            }
            else if (type == RESOURCE_MODEL) {
                this->textBoxResourceType->Text = "Model Resource";
                this->buttonExport->Text = "Export to DFF";
                this->buttonExport->Visible = true;
                this->buttonExport->Enabled = true;
                this->treeViewData->Nodes->Clear();
                this->treeViewData->Visible = true;
                // strcat(name, ".mdl");
            
                if (pakOpened) {
                    pak = fopen(lastPakPath, "rb");
                    fseek(pak, pakArchive.getResourceOffset(id), SEEK_SET);
                    fseek(pak, offset, SEEK_SET);
                    fread(&modelHeader, 48, 1, pak);
                }
                else {
                    pak = fopen(lastDXTPath, "rb");
                    fseek(pak, dxtPack.offsets[id], SEEK_SET);
                    fread(&modelHeader, 48, 1, pak);
                }
            
                if (modelHeader.numVertices > 0) {
                    verts = new ModelVertex[modelHeader.numVertices];
                    fread(verts, sizeof(ModelVertex), modelHeader.numVertices, pak);
                }
                if (modelHeader.numMatrices > 0) {
                    matrices = new ModelMatrix[modelHeader.numMatrices - 1];
                    fread(matrices, sizeof(ModelMatrix), modelHeader.numMatrices - 1, pak);
                }
                if (modelHeader.numMaterials > 0) {
                    materials = new ModelMaterial[modelHeader.numMaterials];
                    fread(materials, sizeof(ModelMaterial), modelHeader.numMaterials, pak);
                }
                fclose(pak);
            
                sprintf(text, "NumVariances: %d", modelHeader.numVariances);
                this->treeViewData->Nodes->Add(gcnew String(text));
                sprintf(text, "NumNodes: %d", modelHeader.numMatrices - 1);
                this->treeViewData->Nodes->Add(gcnew String(text));
                sprintf(text, "NumMaterials: %d", modelHeader.numMaterials);
                this->treeViewData->Nodes->Add(gcnew String(text));
                sprintf(text, "NumVertices: %d", modelHeader.numVertices);
                this->treeViewData->Nodes->Add(gcnew String(text));
                sprintf(text, "field_8: %d", modelHeader.unknown1);
                this->treeViewData->Nodes->Add(gcnew String(text));
                sprintf(text, "field_C: %d", modelHeader.unknown2);
                this->treeViewData->Nodes->Add(gcnew String(text));
            
                TreeNode ^boundNodeAA = this->treeViewData->Nodes->Add("BoundMin");
                sprintf(text, "X: %d", modelHeader.unknown3[0]);
                boundNodeAA->Nodes->Add(gcnew String(text));
                sprintf(text, "Y: %d", modelHeader.unknown3[1]);
                boundNodeAA->Nodes->Add(gcnew String(text));
                sprintf(text, "Z: %d", modelHeader.unknown3[2]);
                boundNodeAA->Nodes->Add(gcnew String(text));
                TreeNode ^boundNodeBB = this->treeViewData->Nodes->Add("BoundMax");
                sprintf(text, "X: %d", modelHeader.unknown3[3]);
                boundNodeBB->Nodes->Add(gcnew String(text));
                sprintf(text, "Y: %d", modelHeader.unknown3[4]);
                boundNodeBB->Nodes->Add(gcnew String(text));
                sprintf(text, "Z: %d", modelHeader.unknown3[5]);
                boundNodeBB->Nodes->Add(gcnew String(text));
                sprintf(text, "field_28: %d", modelHeader.unknown3[6]);
                this->treeViewData->Nodes->Add(gcnew String(text));
                sprintf(text, "field_2C: %d", modelHeader.unknown3[7]);
                this->treeViewData->Nodes->Add(gcnew String(text));
                sprintf(text, "Vertices (%d)", modelHeader.numVertices);
                verticesNode = this->treeViewData->Nodes->Add(gcnew String(text));
                for (int i = 0; i < modelHeader.numVertices; i++) {
                    sprintf(text, "Vertex %d", i);
                    vertexNode = verticesNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "position  %d %d %d", verts[i].x, verts[i].y, verts[i].z);
                    vertexNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "normal    %d %d %d", verts[i].nx, verts[i].ny, verts[i].nz);
                    vertexNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "texcoord  %d %d", verts[i].u, verts[i].v);
                    vertexNode->Nodes->Add(gcnew String(text));
                }
            
                sprintf(text, "Nodes (%d)", modelHeader.numMatrices - 1);
                matricesNode = this->treeViewData->Nodes->Add(gcnew String(text));
                for (int i = 0; i < (modelHeader.numMatrices - 1); i++) {
                    sprintf(text, "Node %d", i);
                    matrixNode = matricesNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "RightX %d", matrices[i].right_x);
                    matrixNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "RightY %d", matrices[i].right_y);
                    matrixNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "RightZ %d", matrices[i].right_z);
                    matrixNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "TopX   %d", matrices[i].top_x);
                    matrixNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "TopY   %d", matrices[i].top_y);
                    matrixNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "TopZ   %d", matrices[i].top_z);
                    matrixNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "AtX    %d", matrices[i].at_x);
                    matrixNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "AtY    %d", matrices[i].at_y);
                    matrixNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "AtZ    %d", matrices[i].at_z);
                    matrixNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "ParentNode  %d", matrices[i].parentNode);
                    matrixNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "field_13 %d", matrices[i].unknown1);
                    matrixNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "PosnX  %d", matrices[i].x);
                    matrixNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "PosnY  %d", matrices[i].y);
                    matrixNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "PosnZ  %d", matrices[i].z);
                    matrixNode->Nodes->Add(gcnew String(text));
                }
            
                sprintf(text, "Materials (%d)", modelHeader.numMaterials);
                materialsNode = this->treeViewData->Nodes->Add(gcnew String(text));
                for (int i = 0; i < modelHeader.numMaterials; i++) {
                    sprintf(text, "Material %d", i);
                    matNode = materialsNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "Texture %d", materials[i].texture);
                    matNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "VertexCount %d", materials[i].vertexCount);
                    matNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "RenderingFlags %d", materials[i].renderingFlags);
                    matNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "Node %d", materials[i].node);
                    matNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "field_6 %d", materials[i].unknown1);
                    matNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "field_7 %d", materials[i].unknown2);
                    matNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "VarianceFlags %d", materials[i].varianceFlags);
                    matNode->Nodes->Add(gcnew String(text));
                }
            
                sprintf(text, "Variances (%d)", modelHeader.numVariances);
                this->treeViewData->Nodes->Add(gcnew String(text));
            
                if (verts)
                    delete[] verts;
                if (matrices)
                    delete[] matrices;
                if (materials)
                    delete[] materials;
            }
            else if (type == RESOURCE_WORLDBLOCK) {
                this->textBoxResourceType->Text = "World Streaming Block";
                this->buttonExport->Visible = true;
                this->buttonExport->Text = "Generate IDE/IPL";
                this->treeViewData->Nodes->Clear();
                this->tabControl1->SelectedIndex = 0;
                if (pakOpened)
                    this->treeViewData->Visible = true;
                else {
                    this->treeViewData->Visible = false;
                    return;
                }
                pak = fopen(lastPakPath, "rb");
                fseek(pak, pakArchive.getResourceOffset(id), SEEK_SET);
                WorldSector wrldSector;
            
                fread(&wrldSector, 40, 1, pak);
                matrixNode = this->treeViewData->Nodes->Add("Transform");
                sprintf(text, "RightX %d", wrldSector.transform.right_x);
                matrixNode->Nodes->Add(gcnew String(text));
                sprintf(text, "RightY %d", wrldSector.transform.right_y);
                matrixNode->Nodes->Add(gcnew String(text));
                sprintf(text, "RightZ %d", wrldSector.transform.right_z);
                matrixNode->Nodes->Add(gcnew String(text));
                sprintf(text, "TopX   %d", wrldSector.transform.top_x);
                matrixNode->Nodes->Add(gcnew String(text));
                sprintf(text, "TopY   %d", wrldSector.transform.top_y);
                matrixNode->Nodes->Add(gcnew String(text));
                sprintf(text, "TopZ   %d", wrldSector.transform.top_z);
                matrixNode->Nodes->Add(gcnew String(text));
                sprintf(text, "AtX    %d", wrldSector.transform.at_x);
                matrixNode->Nodes->Add(gcnew String(text));
                sprintf(text, "AtY    %d", wrldSector.transform.at_y);
                matrixNode->Nodes->Add(gcnew String(text));
                sprintf(text, "AtZ    %d", wrldSector.transform.at_z);
                matrixNode->Nodes->Add(gcnew String(text));
                sprintf(text, "Padding  %d", wrldSector.transform.padding);
                matrixNode->Nodes->Add(gcnew String(text));
                sprintf(text, "PosnX  %d", wrldSector.transform.x);
                matrixNode->Nodes->Add(gcnew String(text));
                sprintf(text, "PosnY  %d", wrldSector.transform.y);
                matrixNode->Nodes->Add(gcnew String(text));
                sprintf(text, "PosnZ  %d", wrldSector.transform.z);
                matrixNode->Nodes->Add(gcnew String(text));
            
                std::list<unsigned int> meshOffsets;
            
                TreeNode ^sectorsNode = this->treeViewData->Nodes->Add("Sectors (4)");
                for (int s = 0; s < 4; s++) {
                    fseek(pak, pakArchive.getResourceOffset(id) + 40 + wrldSector.sectorOffsets[s], SEEK_SET);
                    Sector sector;
                    fread(&sector, 12, 1, pak);
                    sprintf(text, "Sector  %d", s);
                    TreeNode ^sectorNode = sectorsNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "Bool1 %d", sector.bool1);
                    sectorNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "Bool2 %d", sector.bool2);
                    sectorNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "NumInstances %d", sector.numInstances);
                    sectorNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "NumLights %d", sector.numLights);
                    sectorNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "NumLevels %d", sector.numLevels);
                    sectorNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "Count6 %d", sector.count6);
                    sectorNode->Nodes->Add(gcnew String(text));
                    sprintf(text, "NumTextures %d", sector.numTextures);
                    sectorNode->Nodes->Add(gcnew String(text));
            
                    sprintf(text, "Levels (%d)", sector.numLevels);
                    TreeNode ^levelsNode = sectorNode->Nodes->Add(gcnew String(text));
                    for (int l = 0; l < sector.numLevels; l++) {
                        sprintf(text, "Level %d", l);
                        TreeNode ^levelNode = levelsNode->Nodes->Add(gcnew String(text));
                        SectorLevel level;
                        fread(&level, 16, 1, pak);
                        sprintf(text, "X %d", level.x);
                        levelNode->Nodes->Add(gcnew String(text));
                        sprintf(text, "Y %d", level.y);
                        levelNode->Nodes->Add(gcnew String(text));
                        sprintf(text, "Z %d", level.z);
                        levelNode->Nodes->Add(gcnew String(text));
                        sprintf(text, "NumInstances %d", level.numInstances);
                        levelNode->Nodes->Add(gcnew String(text));
                        sprintf(text, "Flags %d", level.flags);
                        levelNode->Nodes->Add(gcnew String(text));
                    }
                    sprintf(text, "Instances (%d)", sector.numInstances);
                    TreeNode ^instancesNode = sectorNode->Nodes->Add(gcnew String(text));
                    for (int i = 0; i < sector.numInstances; i++) {
                        sprintf(text, "Instance %d", i);
                        TreeNode ^instanceNode = instancesNode->Nodes->Add(gcnew String(text));
                        ModelInstance instance;
                        fread(&instance, 16, 1, pak);
                        sprintf(text, "Id %d", instance.id);
                        instanceNode->Nodes->Add(gcnew String(text));
                        sprintf(text, "RenderListId %d", instance.renderListId);
                        instanceNode->Nodes->Add(gcnew String(text));
                        sprintf(text, "BuildingSwap %d", instance.buildingSwap);
                        instanceNode->Nodes->Add(gcnew String(text));
                        sprintf(text, "ResourceId %d", instance.resourceId);
                        instanceNode->Nodes->Add(gcnew String(text));
                        sprintf(text, "MeshOffset %d", instance.offsetToMesh);
                        instanceNode->Nodes->Add(gcnew String(text));
                        sprintf(text, "Ptr(Empty) %p", instance.ptr_unused);
                        instanceNode->Nodes->Add(gcnew String(text));
            
                        bool found = false;
                        for (auto m = meshOffsets.begin(); m != meshOffsets.end(); m++) {
                            if (*m == instance.offsetToMesh) {
                                found = true;
                                break;
                            }
                        }
                        if (!found)
                            meshOffsets.push_back(instance.offsetToMesh);
                    }
                    sprintf(text, "Lights (%d)", sector.numLights);
                    TreeNode ^lightsNode = sectorNode->Nodes->Add(gcnew String(text));
                    for (int l = 0; l < sector.numLights; l++) {
                        sprintf(text, "Light %d", l);
                        TreeNode ^lightNode = lightsNode->Nodes->Add(gcnew String(text));
                        Light light;
                        fread(&light, 20, 1, pak);
                        sprintf(text, "A %d", light.a);
                        lightNode->Nodes->Add(gcnew String(text));
                        sprintf(text, "B %d", light.b);
                        lightNode->Nodes->Add(gcnew String(text));
                        sprintf(text, "C %d", light.c);
                        lightNode->Nodes->Add(gcnew String(text));
                        sprintf(text, "D %d", light.d);
                        lightNode->Nodes->Add(gcnew String(text));
                        sprintf(text, "E %d", light.e);
                        lightNode->Nodes->Add(gcnew String(text));
                    }
                    sprintf(text, "Unknown (%d)", sector.count6);
                    TreeNode ^unksNode = sectorNode->Nodes->Add(gcnew String(text));
                    for (int c = 0; c < sector.count6; c++) {
                        sprintf(text, "Unknown %d", c);
                        TreeNode ^unkNode = lightsNode->Nodes->Add(gcnew String(text));
                        Unk20 unk20;
                        fread(&unk20, 20, 1, pak);
                        sprintf(text, "A %d", unk20.a);
                        unkNode->Nodes->Add(gcnew String(text));
                        sprintf(text, "B %d", unk20.b);
                        unkNode->Nodes->Add(gcnew String(text));
                        sprintf(text, "C %d", unk20.c);
                        unkNode->Nodes->Add(gcnew String(text));
                        sprintf(text, "D %d", unk20.d);
                        unkNode->Nodes->Add(gcnew String(text));
                        sprintf(text, "E %d", unk20.e);
                        unkNode->Nodes->Add(gcnew String(text));
                    }
                    sprintf(text, "Textures (%d)", sector.numTextures);
                    TreeNode ^texturesNode = sectorNode->Nodes->Add(gcnew String(text));
                    for (int t = 0; t < sector.numTextures; t++) {
                        short textureId;
                        fread(&textureId, 2, 1, pak);
                        sprintf(text, "%d", textureId);
                        texturesNode->Nodes->Add(gcnew String(text));
                    }
                }
                sprintf(text, "Models (%d)", meshOffsets.size());
                this->treeViewData->Nodes->Add(gcnew String(text));
            }
            else if (type == RESOURCE_TEXT && romOpened) {
                this->textBoxResourceType->Text = "Text Resource";
                this->buttonExport->Text = "Export to TXT";
                this->buttonExport->Visible = true;
                this->treeViewData->Nodes->Clear();
                this->treeViewData->Visible = true;
                this->tabControl1->SelectedIndex = 0;
            
                char path[512];
                strcpy(path, lastROMPath);
                strrchr(path, '\\')[1] = '\0';
                strcat(path, "ROM.WAD");
                FILE *rom = fopen(path, "rb");
                unsigned int size = romData.entries[id].size;
                unsigned char *data = new unsigned char[size];
                fseek(rom, romData.entries[id].offset, SEEK_SET);
                fread(data, size, 1, rom);
                fclose(rom);
                cGXTFile gxt(data);
                delete[] data;
                for (int i = 0; i < gxt.stringCount; i++)
                    this->treeViewData->Nodes->Add(gcnew String(gxt.strings[i]));
                this->buttonExport->Enabled = true;
            }
            else {
                this->textBoxResourceType->Text = "Resource";
                this->tabControl1->SelectedIndex = 0;
            
                if (!strncmp(name, "globalt", 7) || !strncmp(name, "globala", 7)) {
                    this->buttonExport->Enabled = false;
                    this->treeViewData->Nodes->Clear();
                    this->treeViewData->Visible = true;
                    pak = fopen(lastPakPath, "rb");
                    fseek(pak, pakArchive.getResourceOffset(id), SEEK_SET);
                    unsigned short numTextures;
                    fread(&numTextures, 2, 1, pak);
                    if (numTextures > 0) {
                        for (int i = 0; i < numTextures; i++) {
                            short id;
                            fread(&id, 2, 1, pak);
                            if (id != -1) {
                                sprintf(text, "texture%d", id);
                                this->treeViewData->Nodes->Add(gcnew String(text));
                            }
                            else
                                this->treeViewData->Nodes->Add("empty");
                        }
                    }
                    fclose(pak);
                    this->buttonExport->Visible = false;
                    this->treeViewData->Nodes->Clear();
                    this->treeViewData->Visible = false;
                }
                else {
                    this->buttonExport->Visible = false;
                    this->treeViewData->Nodes->Clear();
                    this->treeViewData->Visible = false;
                }
            }
            this->textBoxResourceType->Visible = true;
        }
    private:
        System::Void buttonExportBinary_Click(System::Object^  sender, System::EventArgs^  e) {
        if (this->treeView1->SelectedNode) {
            if (pakOpened || dxtOpened) {
                unsigned int id, type, offset;
                char name[64];
                pakArchive.NodeGetInfo((char*)(void*)Marshal::StringToHGlobalAnsi(this->treeView1->SelectedNode->Text),
                    &id, &type, &offset, name);
                //gtaRwErrorSet("%s id %d type %d offset 0x%X", name, id, type, offset);
                SaveFileDialog^ dlg = gcnew SaveFileDialog();
                switch (type) {
                case RESOURCE_TEXTURE:
                    dlg->Filter = "GTACW Texture|*.tex";
                    break;
                case RESOURCE_MODEL:
                    dlg->Filter = "GTACW Model|*.mdl";
                    break;
                case RESOURCE_WORLDBLOCK:
                    dlg->Filter = "GTACW Streaming Block|*.wbl";
                    break;
                default:
                    dlg->Filter = "GTACW Resource|*.res";
                    break;
                }
                dlg->FileName = gcnew String(name);
                if (dlg->ShowDialog() == Windows::Forms::DialogResult::OK) {
                    unsigned int size;
                    FILE *pak;
                    if (pakOpened) {
                        pak = fopen(lastPakPath, "rb");
                        size = pakArchive.getResourceSize(id);
                        fseek(pak, pakArchive.getResourceOffset(id), SEEK_SET);
                    }
                    else {
                        pak = fopen(lastDXTPath, "rb");
                        fseek(pak, dxtPack.offsets[id], SEEK_SET);
                        size = dxtPack.sizes[id];
                    }
                    char * data = new char[size];
                    fread(data, size, 1, pak);
                    fclose(pak);
                    FILE *file = fopen((char*)(void*)Marshal::StringToHGlobalAnsi(dlg->FileName), "wb");
                    fwrite(data, pakArchive.getResourceSize(id), 1, file);
                    delete[] data;
                    fclose(file);
                }
            }
            else if (romOpened) {
                unsigned int id, type, offset;
                char name[64];
                pakArchive.NodeGetInfo((char*)(void*)Marshal::StringToHGlobalAnsi(this->treeView1->SelectedNode->Text),
                    &id, &type, &offset, name);
                //gtaRwErrorSet("%s id %d type %d offset 0x%X", name, id, type, offset);
                SaveFileDialog^ dlg = gcnew SaveFileDialog();
                switch (type) {
                case RESOURCE_TEXTURE:
                    dlg->Filter = "GTACW Texture|*.tex";
                    break;
                case RESOURCE_MODEL:
                    dlg->Filter = "GTACW Model|*.mdl";
                    break;
                case RESOURCE_WORLDBLOCK:
                    dlg->Filter = "GTACW Streaming Block|*.wbl";
                    break;
                case RESOURCE_DATA:
                    dlg->Filter = "GTACW Data File|*.dat";
                    break;
                case RESOURCE_BINARY:
                    dlg->Filter = "GTACW Binary File|*.bin";
                    break;
                case RESOURCE_PALETTE:
                    dlg->Filter = "GTACW Palette|*.pal";
                    break;
                case RESOURCE_TEXT:
                    dlg->Filter = "GTACW Text Table|*.gxt";
                    break;
                case RESOURCE_RAW:
                    dlg->Filter = "GTACW Raw Data|*.raw";
                    break;
                default:
                    dlg->Filter = "GTACW Resource|*.res";
                    break;
                }
                dlg->FileName = gcnew String(name);
                if (dlg->ShowDialog() == Windows::Forms::DialogResult::OK) {
                    char path[512];
                    strcpy(path, lastROMPath);
                    strrchr(path, '\\')[1] = '\0';
                    strcat(path, "ROM.WAD");
                    FILE *rom = fopen(path, "rb");
                    unsigned int size = romData.entries[id].size;
                    char *data = new char[size];
                    fseek(rom, romData.entries[id].offset, SEEK_SET);
                    fread(data, size, 1, rom);
                    fclose(rom);
                    FILE *file = fopen((char*)(void*)Marshal::StringToHGlobalAnsi(dlg->FileName), "wb");
                    fwrite(data, romData.entries[id].size, 1, file);
                    delete[] data;
                    fclose(file);
                }
            }
        }
    }
    private:
        System::Void treeView2_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {

        }
    private:
        System::Void buttonExport_Click(System::Object^  sender, System::EventArgs^  e) {
            if (this->treeView1->SelectedNode) {
                unsigned int id, type, offset;
                char name[64];
                pakArchive.NodeGetInfo((char*)(void*)Marshal::StringToHGlobalAnsi(this->treeView1->SelectedNode->Text),
                    &id, &type, &offset, name);
                if (type == RESOURCE_TEXTURE) {
                    FILE *pak;
                    SaveFileDialog^ dlg = gcnew SaveFileDialog();
                    dlg->Filter = "Portable Network Graphics (PNG)|*.png";
                    dlg->FileName = gcnew String(name);
                    if (dlg->ShowDialog() == Windows::Forms::DialogResult::OK) {
                        unsigned int size;
                        if (pakOpened) {
                            pak = fopen(lastPakPath, "rb");
                            fseek(pak, pakArchive.getResourceOffset(id), SEEK_SET);
                            size = pakArchive.getResourceSize(id);
                        }
                        else {
                            pak = fopen(lastDXTPath, "rb");
                            fseek(pak, dxtPack.offsets[id], SEEK_SET);
                            size = dxtPack.sizes[id];
                        }
            
                        DoTextureExport(pak, (char*)(void*)Marshal::StringToHGlobalAnsi(dlg->FileName),
                            size);
                        fclose(pak);
                    }
                }
                else if (type == RESOURCE_MODEL && pakOpened) {
                    SaveFileDialog^ dlg = gcnew SaveFileDialog();
                    dlg->Filter = "GTA San Andreas 3D Model (DFF)|*.dff";
                    dlg->FileName = gcnew String(name);
                    if (dlg->ShowDialog() == Windows::Forms::DialogResult::OK) {
                        FILE *pak = fopen(lastPakPath, "rb");
                        fseek(pak, offset, SEEK_SET);
                        DoDffExport(pak, name, (char*)(void*)Marshal::StringToHGlobalAnsi(dlg->FileName));
                        fclose(pak);
                    }
                }
                else if (type == RESOURCE_TEXT && romOpened) {
                    SaveFileDialog^ dlg = gcnew SaveFileDialog();
                    dlg->Filter = "Text File (TXT)|*.txt";
                    dlg->FileName = gcnew String(name);
                    if (dlg->ShowDialog() == Windows::Forms::DialogResult::OK) {
                        char path[512];
                        strcpy(path, lastROMPath);
                        strrchr(path, '\\')[1] = '\0';
                        strcat(path, "ROM.WAD");
                        FILE *rom = fopen(path, "rb");
                        unsigned int size = romData.entries[id].size;
                        unsigned char *data = new unsigned char[size];
                        fseek(rom, romData.entries[id].offset, SEEK_SET);
                        fread(data, size, 1, rom);
                        fclose(rom);
                        cGXTFile gxt(data);
                        gxt.Flush((char*)(void*)Marshal::StringToHGlobalAnsi(dlg->FileName));
                        delete[] data;
                    }
                }
                else if (type == RESOURCE_WORLDBLOCK && pakOpened) {
                    if (vistaFolderBrowserDialog1->ShowDialog() == Windows::Forms::DialogResult::OK) {
                        FILE *pakFile = fopen(lastPakPath, "rb");
                        fseek(pakFile, offset, SEEK_SET);
                        WorldSector wrldSector;
                        fread(&wrldSector, 40, 1, pakFile);
                        std::list<unsigned int> meshOffsets;
            
                        unsigned int worldSectorId;
                        sscanf(&name[10], "%d", &worldSectorId);
            
                        char iplPath[512];
                        strcpy(iplPath, (char*)(void*)Marshal::StringToHGlobalAnsi(vistaFolderBrowserDialog1->SelectedPath));
                        strcat(iplPath, "\\");
                        strcat(iplPath, name);
                        strcat(iplPath, ".ipl");
            
                        FILE *ipl = fopen(iplPath, "wt");
                        fputs("inst\n", ipl);
                        for (int s = 0; s < 4; s++) {
                            fseek(pakFile, offset + 40 + wrldSector.sectorOffsets[s], SEEK_SET);
                            Sector sector;
                            fread(&sector, 12, 1, pakFile);
                            for (int l = 0; l < sector.numLevels; l++) {
                                SectorLevel level;
                                fread(&level, 16, 1, pakFile);
                            }
                            for (int inst = 0; inst < sector.numInstances; inst++) {
                                ModelInstance instance;
                                fread(&instance, 16, 1, pakFile);
                                bool found = false;
                                for (auto m = meshOffsets.begin(); m != meshOffsets.end(); m++) {
                                    if (*m == instance.offsetToMesh) {
                                        found = true;
                                        break;
                                    }
                                }
                                if (!found)
                                    meshOffsets.push_back(instance.offsetToMesh);
                                char modelName[32];
            
                                sprintf(modelName, "worldmodel%d_%d", worldSectorId, meshOffsets.size() - 1);
                                fprintf(ipl, "%d, %s, 0, %f, %f, %f, 0, 0, 0, 1, 0\n", instance.offsetToMesh, modelName,
                                    (float)wrldSector.transform.x / 4096.0f,
                                    (float)wrldSector.transform.y / 4096.0f,
                                    (float)wrldSector.transform.z / 4096.0f);
                            }
                        }
                        fputs("end", ipl);
                        fclose(ipl);
            
                        char idePath[512];
                        strcpy(idePath, (char*)(void*)Marshal::StringToHGlobalAnsi(vistaFolderBrowserDialog1->SelectedPath));
                        strcat(idePath, "\\");
                        strcat(idePath, name);
                        strcat(idePath, ".ide");
            
                        FILE *ide = fopen(idePath, "wt");
                        fputs("objs\n", ide);
            
                        unsigned int counter = 0;
                        for (auto m = meshOffsets.begin(); m != meshOffsets.end(); m++) {
                            fseek(pakFile, offset + *m, SEEK_SET);
                            char modelName[32];
                            sprintf(modelName, "worldmodel%d_%d", worldSectorId, counter);
                            fprintf(ide, "%d, %s, %s, 0, 299\n", *m, modelName, "generic");
            
                            counter++;
                        }
            
                        fputs("end\n", ide);
                        fclose(ide);
            
                        fclose(pakFile);
                    }
                }
            }
        }
    private:
        System::Void menuItem5_Click(System::Object^  sender, System::EventArgs^  e) {
            OpenFileDialog^ dlg = gcnew OpenFileDialog();
            dlg->Filter = "GTA Chinatown Wars DXT Package|*.bin";
            if (dlg->ShowDialog() == Windows::Forms::DialogResult::OK) {
                pakOpened = false;
                dxtOpened = true;
                romOpened = false;
                modelNames.clear();
            
                this->textBoxResourceType->Text = "";
                this->buttonExport->Visible = false;
                this->treeViewData->Nodes->Clear();
                this->treeView1->Nodes->Clear();
                this->textBoxNumResources->Text = "";
                this->treeViewData->Visible = false;
                this->pictureBox1->Visible = false;
                this->tabPage2->Visible = false;
            
                if (pakArchive.pResourceOffsets) {
                    delete[] pakArchive.pResourceOffsets;
                    pakArchive.pResourceOffsets = NULL;
                }
                strcpy(lastDXTPath, (char*)(void*)Marshal::StringToHGlobalAnsi(dlg->FileName));
                FILE *file = fopen(lastDXTPath, "rb");
                if (!file)
                    return;
                fread(&dxtPack.offsets, 4, 8192, file);
                unsigned int count = 0;
                for (int i = 0; i < 8192; i++) {
                    if (dxtPack.offsets[i]) {
                        char name[64];
                        sprintf(name, "texture%d.tex (id %d @ 0x%X)", i, i, dxtPack.offsets[i]);
                        this->treeView1->Nodes->Add(gcnew String(name));
                        dxtPack.sizes[i] = 0;
                        bool found = false;
                        for (int j = i + 1; j < 8192; j++) {
                            if (dxtPack.offsets[j]) {
                                dxtPack.sizes[i] = dxtPack.offsets[j] - dxtPack.offsets[i];
                                found = true;
                                break;
                            }
                        }
                        if (!found) {
                            fseek(file, 0, SEEK_END);
                            unsigned int fileend = ftell(file);
                            dxtPack.sizes[i] = fileend - dxtPack.offsets[i];
                        }
                        count++;
                    }
                }
                char text[128];
                sprintf(text, "%d resources", count);
                this->textBoxNumResources->Text = gcnew String(text);
                fclose(file);
                this->Text = "CTW-Explorer - DXT.bin";
            }
        }
    private:
        System::Void menuItem7_Click(System::Object^  sender, System::EventArgs^  e) {
            if (vistaFolderBrowserDialog1->ShowDialog() == Windows::Forms::DialogResult::OK) {
                if (pakOpened) {
                    FILE *file = fopen(lastPakPath, "rb");
                    for (int i = 0; i < pakArchive.resourcesCount; i++) {
                        if (pakArchive.GetResourceType(i, file) == RESOURCE_TEXTURE) {
                            char path[512];
                            strcpy(path, (char*)(void*)Marshal::StringToHGlobalAnsi(vistaFolderBrowserDialog1->SelectedPath));
                            char name[32];
                            sprintf(name, "\\texture%d.png", i);
                            strcat(path, name);
                            fseek(file, pakArchive.getResourceOffset(i), SEEK_SET);
                            DoTextureExport(file, path, pakArchive.getResourceSize(i));
                        }
                    }
                    fclose(file);
                }
                else if (dxtOpened) {
                    FILE *file = fopen(lastDXTPath, "rb");
                    for (int i = 0; i < 8192; i++) {
                        if (dxtPack.offsets[i]) {
                            char path[512];
                            strcpy(path, (char*)(void*)Marshal::StringToHGlobalAnsi(vistaFolderBrowserDialog1->SelectedPath));
                            char name[32];
                            sprintf(name, "\\texture%d.png", i);
                            strcat(path, name);
                            fseek(file, dxtPack.offsets[i], SEEK_SET);
                            DoTextureExport(file, path, dxtPack.sizes[i]);
                        }
                    }
                    fclose(file);
                }
            }
        }
    private:
        System::Void menuItem3_Click(System::Object^  sender, System::EventArgs^  e) {
            OpenFileDialog^ dlg = gcnew OpenFileDialog();
            dlg->Filter = "GTA Chinatown Wars ROM File|*.WAD";
            if (dlg->ShowDialog() == Windows::Forms::DialogResult::OK) {
                pakOpened = false;
                dxtOpened = false;
                romOpened = true;
                modelNames.clear();
            
                this->textBoxResourceType->Text = "";
                this->buttonExport->Visible = false;
                this->treeViewData->Nodes->Clear();
                this->treeView1->Nodes->Clear();
                this->textBoxNumResources->Text = "";
                this->treeViewData->Visible = false;
                this->pictureBox1->Visible = false;
                this->tabPage2->Visible = false;
            
                if (pakArchive.pResourceOffsets) {
                    delete[] pakArchive.pResourceOffsets;
                    pakArchive.pResourceOffsets = NULL;
                }
                strcpy(lastROMPath, (char*)(void*)Marshal::StringToHGlobalAnsi(dlg->FileName));
                char path[512];
                strcpy(path, lastROMPath);
                strrchr(path, '\\')[1] = '\0';
                strcat(path, "ROM.TOC");
                FILE *file = fopen(path, "rb");
                if (!file)
                    return;
                char text[128];
                fseek(file, 0, SEEK_END);
                unsigned int size = ftell(file);
            
                romData.numEntries = size / 12;
            
                fseek(file, 0, SEEK_SET);
                fread(romData.entries, 12, romData.numEntries, file);
                fclose(file);
                this->Text = "CTW-Explorer - ROW.WAD";
                romData.MapResourceNames();
                unsigned int counter = 0;
                for (int i = 0; i < romData.numEntries; i++) {
                    char name[64];
                    if (modelNames.getName(romData.entries[i].hash))
                        sprintf(name, "%s (id %d @ 0x%X)", modelNames.getName(romData.entries[i].hash), i, romData.entries[i].offset);
                    else {
                        if (romData.entries[i].size > 6) {
                            char rompath[512];
                            strcpy(rompath, lastROMPath);
                            strrchr(rompath, '\\')[1] = '\0';
                            strcat(rompath, "ROM.WAD");
                            FILE *rom = fopen(rompath, "rb");
                            char romdata[8];
                            fseek(rom, romData.entries[i].offset, SEEK_SET);
                            fread(romdata, 6, 1, rom);
                            fclose(rom);
                            if (!strncmp(romdata, "DS_GXT", 6))
                                sprintf(name, "%X.gxt (id %d @ 0x%X)", romData.entries[i].hash, i, romData.entries[i].offset);
                            else
                                sprintf(name, "%X.res (id %d @ 0x%X)", romData.entries[i].hash, i, romData.entries[i].offset);
                        }
                        else
                            sprintf(name, "%X.res (id %d @ 0x%X)", romData.entries[i].hash, i, romData.entries[i].offset);
                    }
                    this->treeView1->Nodes->Add(gcnew String(name));
                    counter++;
                }
                sprintf(text, "%d resources", size / 12);
                this->textBoxNumResources->Text = gcnew String(text);
            }
        }
    private:
        System::Void menuItem8_Click(System::Object^  sender, System::EventArgs^  e) {
            if (vistaFolderBrowserDialog1->ShowDialog() == Windows::Forms::DialogResult::OK) {
                if (pakOpened) {
                    FILE *pakFile = fopen(lastPakPath, "rb");
                    unsigned int offset = pakArchive.getResourceOffset(0);
                    fseek(pakFile, offset, SEEK_SET);
                    short resTableIds[23];
                    fread(resTableIds, 56, 1, pakFile);
                    if (resTableIds[0] != -1) {
                        modelNames.setName(resTableIds[0], "worldstreamblocks.res");
                        unsigned int offset = pakArchive.getResourceOffset(resTableIds[0]);
                        fseek(pakFile, offset, SEEK_SET);
                        fseek(pakFile, 8, SEEK_CUR);
                        short blockIds[2478];
                        fread(&blockIds, 2, 2478, pakFile);
                        char selectedPath[512];
                        strcpy(selectedPath, (char*)(void*)Marshal::StringToHGlobalAnsi(vistaFolderBrowserDialog1->SelectedPath));
                        for (int i = 0; i < 2478; i++) {
                            if (blockIds[i] != -1) {
                                char folderPath[512];
                                strcpy(folderPath, selectedPath);
                                char name[32];
                                sprintf(name, "\\worldblock%d", i);
                                strcat(folderPath, name);
                                CreateDirectory(folderPath, NULL);
                                fseek(pakFile, pakArchive.getResourceOffset(blockIds[i]), SEEK_SET);
                                WorldSector wrldSector;
                                fread(&wrldSector, 40, 1, pakFile);
                                std::list<unsigned int> meshOffsets;
                                for (int s = 0; s < 4; s++) {
                                    fseek(pakFile, pakArchive.getResourceOffset(blockIds[i]) + 40 + wrldSector.sectorOffsets[s], SEEK_SET);
                                    Sector sector;
                                    fread(&sector, 12, 1, pakFile);
                                    for (int l = 0; l < sector.numLevels; l++) {
                                        SectorLevel level;
                                        fread(&level, 16, 1, pakFile);
                                    }
                                    for (int inst = 0; inst < sector.numInstances; inst++) {
                                        ModelInstance instance;
                                        fread(&instance, 16, 1, pakFile);
                                        bool found = false;
                                        for (auto m = meshOffsets.begin(); m != meshOffsets.end(); m++) {
                                            if (*m == instance.offsetToMesh) {
                                                found = true;
                                                break;
                                            }
                                        }
                                        if (!found)
                                            meshOffsets.push_back(instance.offsetToMesh);
                                    }
                                }
                                unsigned int counter = 0;
                                for (auto m = meshOffsets.begin(); m != meshOffsets.end(); m++) {
                                    fseek(pakFile, pakArchive.getResourceOffset(blockIds[i]) + *m, SEEK_SET);
                                    char modelName[32];
                                    sprintf(modelName, "worldmodel%d_%d", i, counter);
                                    char fileName[512];
                                    strcpy(fileName, folderPath);
                                    strcat(fileName, "\\");
                                    strcat(fileName, modelName);
                                    strcat(fileName, ".dff");
                                    DoDffExport(pakFile, modelName, fileName);
                                    counter++;
                                }
                            }
                        }
                    }
                    fclose(pakFile);
                }
            }
        }
    private:
        System::Void menuItem4_Click(System::Object^  sender, System::EventArgs^  e) {
            if (vistaFolderBrowserDialog1->ShowDialog() == Windows::Forms::DialogResult::OK) {
                if (pakOpened) {
                    FILE *pakFile = fopen(lastPakPath, "rb");
                    unsigned int offset = pakArchive.getResourceOffset(0);
                    fseek(pakFile, offset, SEEK_SET);
                    short resTableIds[23];
                    fread(resTableIds, 56, 1, pakFile);
                    if (resTableIds[0] != -1) {
                        unsigned int offset = pakArchive.getResourceOffset(resTableIds[0]);
                        fseek(pakFile, offset, SEEK_SET);
                        fseek(pakFile, 8, SEEK_CUR);
                        short blockIds[2478];
                        fread(&blockIds, 2, 2478, pakFile);
                        char selectedPath[512];
                        strcpy(selectedPath, (char*)(void*)Marshal::StringToHGlobalAnsi(vistaFolderBrowserDialog1->SelectedPath));
                        for (int i = 0; i < 2478; i++) {
                            if (blockIds[i] != -1) {
                                char folderPath[512];
                                strcpy(folderPath, selectedPath);
                                fseek(pakFile, pakArchive.getResourceOffset(blockIds[i]), SEEK_SET);
                                WorldSector wrldSector;
                                fread(&wrldSector, 40, 1, pakFile);
                                std::list<unsigned int> meshOffsets;
                                char name[32];
                                sprintf(name, "worldblock%d", i);
                                char iplPath[512];
                                strcpy(iplPath, selectedPath);
                                strcat(iplPath, "\\");
                                strcat(iplPath, name);
                                strcat(iplPath, ".ipl");
                                FILE *ipl = fopen(iplPath, "wt");
                                fputs("inst\n", ipl);
                                for (int s = 0; s < 4; s++) {
                                    fseek(pakFile, pakArchive.getResourceOffset(blockIds[i]) + 40 + wrldSector.sectorOffsets[s], SEEK_SET);
                                    Sector sector;
                                    fread(&sector, 12, 1, pakFile);
                                    for (int l = 0; l < sector.numLevels; l++) {
                                        SectorLevel level;
                                        fread(&level, 16, 1, pakFile);
                                    }
                                    for (int inst = 0; inst < sector.numInstances; inst++) {
                                        ModelInstance instance;
                                        fread(&instance, 16, 1, pakFile);
                                        bool found = false;
                                        for (auto m = meshOffsets.begin(); m != meshOffsets.end(); m++) {
                                            if (*m == instance.offsetToMesh) {
                                                found = true;
                                                break;
                                            }
                                        }
                                        if (!found)
                                            meshOffsets.push_back(instance.offsetToMesh);
                                        char modelName[32];
            
                                        sprintf(modelName, "worldmodel%d_%d", i, meshOffsets.size() - 1);
                                        fprintf(ipl, "%d, %s, 0, %f, %f, %f, 0, 0, 0, 1, 0\n", instance.offsetToMesh, modelName,
                                            (float)wrldSector.transform.x / 4096.0f,
                                            (float)wrldSector.transform.y / 4096.0f,
                                            (float)wrldSector.transform.z / 4096.0f);
                                    }
                                }
                                fputs("end", ipl);
                                fclose(ipl);
            
                                char idePath[512];
                                strcpy(idePath, selectedPath);
                                strcat(idePath, "\\");
                                strcat(idePath, name);
                                strcat(idePath, ".ide");
            
                                FILE *ide = fopen(idePath, "wt");
                                fputs("objs\n", ide);
            
                                unsigned int counter = 0;
                                for (auto m = meshOffsets.begin(); m != meshOffsets.end(); m++) {
                                    fseek(pakFile, pakArchive.getResourceOffset(blockIds[i]) + *m, SEEK_SET);
                                    char modelName[32];
                                    sprintf(modelName, "worldmodel%d_%d", i, counter);
            
                                    fprintf(ide, "%d, %s, %s, 0, 299\n", *m, modelName, "generic");

                                    counter++;
                                }
                                fputs("end\n", ide);
                                fclose(ide);
                            }
                        }
                    }
                    fclose(pakFile);
                }
            }
        }
    private:
        System::Void menuItem9_Click(System::Object^  sender, System::EventArgs^  e) {
            if (vistaFolderBrowserDialog1->ShowDialog() == Windows::Forms::DialogResult::OK) {
                if (pakOpened) {
                    FILE *pakFile = fopen(lastPakPath, "rb");
                    unsigned int offset = pakArchive.getResourceOffset(0);
                    fseek(pakFile, offset, SEEK_SET);
                    short resTableIds[23];
                    fread(resTableIds, 56, 1, pakFile);
                    if (resTableIds[0] != -1) {
                        unsigned int offset = pakArchive.getResourceOffset(resTableIds[0]);
                        fseek(pakFile, offset, SEEK_SET);
                        fseek(pakFile, 8, SEEK_CUR);
                        short blockIds[2478];
                        fread(&blockIds, 2, 2478, pakFile);
                        char selectedPath[512];
                        strcpy(selectedPath, (char*)(void*)Marshal::StringToHGlobalAnsi(vistaFolderBrowserDialog1->SelectedPath));
            
                        FILE *fmap = fopen("mapdivision.txt", "rt");
                        if (!fmap) {
                            fclose(pakFile);
                            return;
                        }
                        unsigned int chunksCount;
                        char line[256];
                        fgets(line, 256, fmap);
                        sscanf(line, "%u", &chunksCount);
                        if (!chunksCount) {
                            fclose(fmap);
                            fclose(pakFile);
                            return;
                        }
            
                        char folderPath[512];
                        strcpy(folderPath, selectedPath);
            
                        unsigned int idCounter = 0;
            
                        for (int ch = 0; ch < chunksCount; ch++) {
                            char name[32];
                            sprintf(name, "worldblock%d", ch);
                            char iplPath[512];
                            strcpy(iplPath, selectedPath);
                            strcat(iplPath, "\\");
                            strcat(iplPath, name);
                            strcat(iplPath, ".ipl");
                            FILE *ipl = fopen(iplPath, "wt");
                            fputs("inst\n", ipl);
            
                            char idePath[512];
                            strcpy(idePath, selectedPath);
                            strcat(idePath, "\\");
                            strcat(idePath, name);
                            strcat(idePath, ".ide");
                            FILE *ide = fopen(idePath, "wt");
                            fputs("objs\n", ide);
                            chunk  tmpchunk;
                            fgets(line, 256, fmap);
                            tmpchunk.count = sscanf(line, "%h %h %h %h %h %h %h %h %h %h %h %h %h %h %h %h",
                                &tmpchunk.arr[0], &tmpchunk.arr[1], &tmpchunk.arr[2], &tmpchunk.arr[3],
                                &tmpchunk.arr[4], &tmpchunk.arr[5], &tmpchunk.arr[6], &tmpchunk.arr[7],
                                &tmpchunk.arr[8], &tmpchunk.arr[9], &tmpchunk.arr[10], &tmpchunk.arr[11],
                                &tmpchunk.arr[12], &tmpchunk.arr[13], &tmpchunk.arr[14], &tmpchunk.arr[15]);
                            for (int i = 0; i < tmpchunk.count; i++) {
                                if (blockIds[tmpchunk.arr[i]] != -1) {
                                    fseek(pakFile, pakArchive.getResourceOffset(blockIds[tmpchunk.arr[i]]), SEEK_SET);
                                    WorldSector wrldSector;
                                    fread(&wrldSector, 40, 1, pakFile);
                                    std::vector<unsigned int> meshOffsets;
            
                                    for (int s = 0; s < 4; s++) {
                                        fseek(pakFile, pakArchive.getResourceOffset(blockIds[tmpchunk.arr[i]]) + 40 + wrldSector.sectorOffsets[s], SEEK_SET);
                                        Sector sector;
                                        fread(&sector, 12, 1, pakFile);
                                        for (int l = 0; l < sector.numLevels; l++) {
                                            SectorLevel level;
                                            fread(&level, 16, 1, pakFile);
                                        }
                                        for (int inst = 0; inst < sector.numInstances; inst++) {
                                            ModelInstance instance;
                                            fread(&instance, 16, 1, pakFile);
                                            bool found = false;
                                            unsigned int id = 0;
                                            for (int m = 0; m < meshOffsets.size(); m++) {
                                                if (meshOffsets[m] == instance.offsetToMesh) {
                                                    id = m;
                                                    found = true;
                                                    break;
                                                }
                                            }
                                            if (!found) {
                                                id = meshOffsets.size();
                                                meshOffsets.push_back(instance.offsetToMesh);
                                            }
                                            char modelName[32];
            
                                            sprintf(modelName, "model%d_%d", tmpchunk.arr[i], id);
                                            fprintf(ipl, "%d, %s, 0, %f, %f, %f, 0, 0, 0, 1, 0\n", id + idCounter, modelName,
                                                (float)wrldSector.transform.x / 4096.0f,
                                                (float)wrldSector.transform.y / 4096.0f,
                                                (float)wrldSector.transform.z / 4096.0f + (float)s * 100.0f);
                                        }
                                    }
            
                                    for (int m = 0; m < meshOffsets.size(); m++) {
                                        fseek(pakFile, pakArchive.getResourceOffset(blockIds[tmpchunk.arr[i]]) + meshOffsets[m], SEEK_SET);
                                        char modelName[32];
                                        sprintf(modelName, "model%d_%d", tmpchunk.arr[i], m);
            
                                        fprintf(ide, "%d, %s, %s, 0, 299\n", m + idCounter, modelName, "generic");
                                    }
                                    idCounter += meshOffsets.size();
                                }
                            }
            
                            fputs("end\n", ide);
                            fclose(ide);
            
                            fputs("end", ipl);
                            fclose(ipl);
                        }
                    }
                    fclose(pakFile);
                }
            }
        }
    private:
        System::Void menuItem10_Click(System::Object^  sender, System::EventArgs^  e) {
            if (vistaFolderBrowserDialog1->ShowDialog() == Windows::Forms::DialogResult::OK) {
                if (pakOpened) {
                    FILE *pakFile = fopen(lastPakPath, "rb");
                    unsigned int offset = pakArchive.getResourceOffset(0);
                    fseek(pakFile, offset, SEEK_SET);
                    short resTableIds[23];
                    fread(resTableIds, 56, 1, pakFile);
                    if (resTableIds[0] != -1) {
                        unsigned int offset = pakArchive.getResourceOffset(resTableIds[0]);
                        fseek(pakFile, offset, SEEK_SET);
                        fseek(pakFile, 8, SEEK_CUR);
                        short blockIds[2478];
                        fread(&blockIds, 2, 2478, pakFile);
                        char selectedPath[512];
                        int maxId = 0;
                        strcpy(selectedPath, (char*)(void*)Marshal::StringToHGlobalAnsi(vistaFolderBrowserDialog1->SelectedPath));
                        for (int i = 0; i < 2478; i++) {
                            if (blockIds[i] != -1) {
                                char folderPath[512];
                                strcpy(folderPath, selectedPath);
                                fseek(pakFile, pakArchive.getResourceOffset(blockIds[i]), SEEK_SET);
                                WorldSector wrldSector;
                                fread(&wrldSector, 40, 1, pakFile);
                                std::list<unsigned int> meshOffsets;
                                char name[32];
                                sprintf(name, "worldblock%d", i);
                                char iplPath[512];
                                strcpy(iplPath, selectedPath);
                                strcat(iplPath, "\\");
                                strcat(iplPath, name);
                                strcat(iplPath, ".dat");
                                FILE *ipl = fopen(iplPath, "wt");
                                for (int s = 0; s < 4; s++) {
                                    fprintf(ipl, "// PART %d\n", s + 1);
                                    fseek(pakFile, pakArchive.getResourceOffset(blockIds[i]) + 40 + wrldSector.sectorOffsets[s], SEEK_SET);
                                    Sector sector;
                                    fread(&sector, 12, 1, pakFile);
                                    fputs("levels\n", ipl);
                                    for (int l = 0; l < sector.numLevels; l++) {
                                        SectorLevel level;
                                        fread(&level, 16, 1, pakFile);
                                    }
                                    fputs("end\n", ipl);
                                    fputs("inst\n", ipl);
                                    for (int inst = 0; inst < sector.numInstances; inst++) {
                                        ModelInstance instance;
                                        fread(&instance, 16, 1, pakFile);
                                        if (instance.id > maxId)
                                            maxId = instance.id;
                                    }
                                    fputs("end\n", ipl);
                                }
                                fclose(ipl);
                            }
                        }
                    }
                    fclose(pakFile);
                }
            }
        }
    private:
        System::Void menuItem12_Click(System::Object^  sender, System::EventArgs^  e) {
            this->menuItem12->Checked = !this->menuItem12->Checked;
            if (this->menuItem12->Checked)
                this->panel1->BackColor = Color::FromArgb(0, 0, 0);
            else
                this->panel1->BackColor = Color::Transparent;
        }
    };
}

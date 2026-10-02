#include<bits/stdc++.h>
using namespace std;


// bad design 
// class DocumentEditor{
//     private:
//        vector<string> documentElements;
//        string rendererdDocument;
//     public:
//     //add text as a plain string
//     void addText(string text){
//      documentElements.push_back(text);
//     }

//     // add image 
//     void addImage(string imagePath){
//         documentElements.push_back(imagePath);
//     }

//     //renders the document by checking the type of each element at runtime

//     string renderDocument(){
//          if(rendererdDocument.empty()){
//              string result;

//             for(auto element: documentElements){
//                 if(element.size()>4 && (element.substr(element.size()-4)== ".jpeg" || 
//             element.substr(element.size()-4)==  ".png")){
//                 result+= "[Image: "+element+"]" + "\n";
//             }else{
//                 result+= element + "\n";
//             }
//             }
//             rendererdDocument = result;
//          }
//          return rendererdDocument;
//     }

//     void saveToFile(){
//         ofstream file("document.txt");
//         if(file.is_open()){
//             file << renderDocument();
//             file.close();
//             cout<<"DOcument saved to document.txt"<<endl;
//         }else{
//             cout<<"Error opening file for writing"<<endl;
//         }
//     }
// };


// good design

class DocumentElement{
    public:
      virtual string render()=0;
};

// concrete implementation for text elements
class TextElement : public DocumentElement{
    private:
        string text;
    public:
        TextElement(string t):text(t){}
        string render() override{
            return text + "\n";
        }
};

// concrete implementation for image elements
class ImageElement : public DocumentElement{
    private:
       string imagePath;
    public:
        ImageElement(string path):imagePath(path){}
        string render() override{
            return "[Image: "+imagePath+"]\n";
        }
};

//Document class responsible for holding a collection of element 
class Document{
    private:
       vector<DocumentElement*> documentElements;
    
    public:
        void addElement(DocumentElement* element){
            documentElements.push_back(element);
        }

        //Renders the document bu concatenating the render output of all elements
        string render(){
            string result;
            for(auto element: documentElements){
                result+=element->render();
            }
            return result;
        }
};

// Persistence class 

class Persistence{
    public:
     virtual void save(string data)=0;
};

//files storage 
class FileStorage : public Persistence{
   public:
    void save(string data) override{
        ofstream outFile("document.txt");
        if(outFile.is_open()){
            outFile<<data;
            outFile.close();
            cout<<"Document saved to document.txt"<<endl;
        }else{
            cout<<"Error opening file for writing"<<endl;
        }
    }
};


//Db storage
class DbStorage : public Persistence{
    public:
        void save(string data) override{
            cout<<"Document saved to database: "<<data<<endl;
        }
};

//DocumentEditor class managing client interactions 
class DocumentEditor{
    private:
       Document* document;
       Persistence* storage;
       string renderedDocument;
    public:
       DocumentEditor(Document* document, Persistence* storage){
        this->document = document;
        this->storage = storage;
       }
       void addText(string text){
        document->addElement(new TextElement(text));
       }
       void addImage(string imagePath){
        document->addElement(new ImageElement(imagePath));
       }
            
       string renderDocument(){
        if(renderedDocument.empty()){
            renderedDocument = document->render();
        }
        return renderedDocument;
       }

       void saveToFile(){
        storage->save(renderDocument());
       }
};
//
int main(){
    // DocumentEditor editor;
    // editor.addText("This is a sample document.");
    // editor.addImage("test.png");
    // editor.addText("This is another paragraph.");

    // cout<<editor.renderDocument()<<endl;
    // editor.saveToFile();
    

    // good design 
    Document* document = new Document();
    Persistence* storage = new FileStorage();
    DocumentEditor* editor = new DocumentEditor(document, storage);

   //Simulate a client using the editor with common text formatting features 

   editor->addText("Hello, World");
   editor->addImage("test.png");
   editor->addText("This is a sample document.");

   cout<<editor->renderDocument()<<endl;
   editor->saveToFile();
    return 0;
}
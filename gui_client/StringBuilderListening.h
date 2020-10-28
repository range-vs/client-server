#pragma once

#include "ConverterString.h"

using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Windows::Markup;
using namespace System::IO;
using namespace System::ComponentModel;
using namespace System::Collections::ObjectModel;
using namespace System::Collections::Generic;
using namespace System::Runtime::CompilerServices;
using namespace System::Runtime;

delegate void StringBuilderListeningTextChanged(System::String^ message);

public ref class StringBuilderListening 
{
    System::Text::StringBuilder^ _builder;

public:
    StringBuilderListening()
    {
        _builder = gcnew System::Text::StringBuilder();
    }

    StringBuilderListening(System::String^ str)
    {
        _builder = gcnew System::Text::StringBuilder(str);
    }


    void Append(System::String^ text) override
    {
        _builder->Append(text);
        TextChanged(text);
        _builder->Clear();
    }

    System::String^ ToString() override
    {
        return _builder->ToString();
    }

    event StringBuilderListeningTextChanged^ TextChanged;

};
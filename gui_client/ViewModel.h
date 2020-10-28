#pragma once

#include "ConverterString.h"
#include "GeneralCommand.h"
#include "Net.h"
#include "StringBuilderListening.h"

#include <vector>
#include <algorithm>
#include <memory>

namespace WpfWindow
{
	using namespace System::Windows;
	using namespace System::Windows::Controls;
	using namespace System::Windows::Markup;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections::ObjectModel;
	using namespace System::Collections::Generic;
	using namespace System::Runtime::CompilerServices;
	using namespace System::Runtime;

	public ref class ViewModel : INotifyPropertyChanged
	{
		System::Threading::Thread^ threadClient;

		System::String^ _textData;
		StringBuilderListening^ _logger;

		System::Boolean _add;
		System::Boolean _check;
		System::Boolean _delete;

		GeneralCommand^ _sendMessage;
		GeneralCommand^ _openFile;

		NetPoint^ net;

		System::String^ currentHash;

	public:

		property System::String^ TextData
		{
			System::String^ get()
			{
				return _textData;
			}

			void set(System::String^ v)
			{
				_textData = v;
				OnPropertyChanged(nameof(TextData));
			}
		}

		void UpdateTextData(System::String^ str);


		property System::Boolean Add
		{
			System::Boolean get()
			{
				return _add;
			}

			void set(System::Boolean v)
			{
				_add = v;
				OnPropertyChanged(nameof(Add));
			}
		}

		property System::Boolean Check
		{
			System::Boolean get()
			{
				return _check;
			}

			void set(System::Boolean v)
			{
				_check = v;
				OnPropertyChanged(nameof(Check));
			}
		}

		property System::Boolean Delete
		{
			System::Boolean get()
			{
				return _delete;
			}

			void set(System::Boolean v)
			{
				_delete = v;
				OnPropertyChanged(nameof(Delete));
			}
		}

		property GeneralCommand^ SendMessage
		{
			GeneralCommand^ get()
			{
				if (_sendMessage == nullptr)
				{
					_sendMessage = gcnew GeneralCommand(gcnew Action<Object^>(this, &ViewModel::SendMessageMethod), nullptr);
				}
				return _sendMessage;
			}
		}

		void SendMessageMethod(Object^ obj);

		property GeneralCommand^ OpenFile
		{
			GeneralCommand^ get()
			{
				if (_openFile == nullptr)
				{
					_openFile = gcnew GeneralCommand(gcnew Action<Object^>(this, &ViewModel::OpenFileMethod), nullptr);
				}
				return _openFile;
			}
		}

		void OpenFileMethod(Object^ obj);

		ViewModel();

	public:
		virtual event System::ComponentModel::PropertyChangedEventHandler^ PropertyChanged;

		void OnPropertyChanged(System::String^ prop);
	
	protected:
		!ViewModel();
	};
}

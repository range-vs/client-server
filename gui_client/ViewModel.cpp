#include "ViewModel.h"
#include "Helper.h"
#include "FileReader.h"
#include "PropertiesReader.h"

namespace WpfWindow
{

	ViewModel::ViewModel()
	{
		Add = true;
		Check = false;
		Delete = false;
		_logger = gcnew StringBuilderListening();
		_logger->TextChanged += gcnew StringBuilderListeningTextChanged(this, &ViewModel::UpdateTextData);
		TextData = gcnew System::String("");
		currentHash = nullptr;

		net = gcnew NetPoint();
		SocketData sd = PropertiesReader::readConfig("configs/client/properties.xml");
		HelpData^ hd = gcnew HelpData(gcnew System::String(sd.address.c_str()), gcnew System::String(sd.port.c_str()), net, _logger);
		System::Threading::Thread^ t = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(hd, &HelpData::ThreadProc));
		t->IsBackground = true;
		t->Start();
	}


	void ViewModel::UpdateTextData(System::String^ str)
	{
		TextData = TextData + str;
	}

	void ViewModel::SendMessageMethod(Object^ obj)
	{
		if (!currentHash)
		{
			TextData += "File no select\n";
			return;
		}
		std::vector<std::pair<System::Boolean, unsigned>> v =
		{
			{Add, 0},
			{Check, 1},
			{Delete, 2}
		};
		auto p = std::find_if(v.begin(), v.end(), FindPair());
		net->SendMessage(currentHash, static_cast<TYPE_OPERATION>(p->second));
	}

	void ViewModel::OpenFileMethod(Object^ obj)
	{
		System::String^ f = FileReader::OpenFile();
		if (!f)
			return;
		TextData += "Selected file: " + f + "\n";
		auto arrBytes = FileReader::ReadFile(f);
		currentHash = gcnew System::String( FileReader::CalculateHash(arrBytes).c_str() );
		TextData += "Hash file: " + currentHash + "\n";
	}

	void ViewModel::OnPropertyChanged(System::String^ prop)
	{
		if (prop)
			PropertyChanged(this, gcnew PropertyChangedEventArgs(prop));
	}
};

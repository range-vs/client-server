#include "Window.h"

namespace WpfWindow
{
	MainWindow::MainWindow()
	{
		this->initializeComponent();
	}

	void MainWindow::initializeComponent()
	{
		// View
		DependencyObject^ rootElement;
		FileStream^ fs = gcnew FileStream(L"configs/client/Window.xaml", FileMode::Open);
		rootElement = (DependencyObject^)XamlReader::Load(fs);
		fs->Close();

		// copy all properties tmp window from this window
		Window^ tmp = (Window^)rootElement;
		this->Width = tmp->Width;
		this->Height = tmp->Height;
		this->Title = tmp->Title;
		this->WindowStartupLocation = tmp->WindowStartupLocation;

		panel = (Panel^)LogicalTreeHelper::FindLogicalNode(rootElement, L"rootPanel");
		this->Content = panel;

		// MVVM
		viewModel = gcnew ViewModel();
		this->DataContext = viewModel;
	}

	MainWindow::~MainWindow()
	{

	}
}


template <int settings_size, int data_size>
class Menu
{
  private:
    Setting *settings[settings_size];
    Data *data[data_size];
    int st_s = settings_size;
    int da_s = data_size;
    
  
  public:
    void send_setting();
    Menu(LiquidCrystal lcd);
    void draw();
    void refresh();
};

Menu::Menu(LiquidCrystal lcd)
{
  for(int i = 0; i < st_s ++)
  {
    settings[i] = new Setting(lcd);
  }

  for(int i = 0; i < da_s; i ++)
  {
    data[i] = new Data(lcd);
  }
}

void Menu::refresh_data()
{
  for(int i = 0; i < da_s)
  {
    data[i].refresh();
  }
}


void Menu::send_setting()
{
  
}


class Setting
{
  public:
    Setting(LiquidCrystal lcd);
};

class Data
{
  public:
    Data(LiquidCrystal lcd);
    void draw();
    
};

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QSettings>
#include <QDir>
#include <vector>

#include "pluginglobal.h"

class IPlugin;

namespace RTPTechGroup {
namespace Plugin {

//! Класс для управления плагинами
/*! Данный класс предназначен для загрузки плагинов,
    получения объектов плагина, сохранение настроек плагина.\n
    Пример:\n
    \code
        QSettings *settings = new QSettings(QSettings::IniFormat, QSettings::UserScope,
                                 QLatin1String("RTPTechGroup"), QLatin1String("UniversalPlatform"));
        PluginManager pluginManager;
        pluginManager.setSettings(settings);
        pluginManager.loadPlugins();
    \endcode

*/

class PLUGINLIB PluginManager : public QObject
{
    Q_OBJECT

    friend class IPlugin;

public:
    //! Получение экземпляра менеджера плагинов
    static PluginManager *instance();

    //! Конструктор плагина
    /*! Производит инициализацию плагина при его создании
    */
    explicit PluginManager(QObject *parent = nullptr);

    //! Деструктор плагина
    /*! Производит завершающие действия при удалении плагина
    */
    ~PluginManager();

    //! Получение объекта для указанного интерфейса
    QObject *interfaceObject(const QString &interfaceName);

    //! Получение объекта для указанного интерфейса с приведением типа
    template<typename T> T interfaceObject(const QString &interfaceName)
    {
        return qobject_cast<T>(m_interfaces.value(interfaceName, nullptr));
    }

    //! Получение объектов для указанного интерфейса
    QList<QObject *> interfaceObjects(const QString &interfaceName);

    //! Получить зависимые плагины
    /*! Позволяет получить список зависимых плагинов от указанного
     */
    QList<IPlugin*> dependentPlugins(IPlugin *plugin);

    //! Получить от каких плагинов зависит
    /*! Позволяет получить список плагинов от которых зависит указанный плагин
     */
    QList<IPlugin *> dependPlugins(IPlugin *plugin);

    //! Загрузка плагинов
    /*! Производит поиск плагина на диске в каталоге
        plugins запущенного приложения и его загрузку
    */
    bool loadPlugins();

    //! Загрузка указанного плагина
    bool loadPlugin(const QString &fileName, const QString &iid = "");

    //! Загрузка следующего плагина
    bool nextLoadPlugins(const QString &iid = "");

    //! Устанавливает ссылку на объект для сохранения настроек
    void setSettings(QSettings *s);

    //! Получает ссылку на объект для сохранения настроек
    QSettings *settings() const;

    //! Получение каталога для плагина
    QDir pluginsDir() const;

    //! Установка каталога для плагина
    void setPluginsDir(const QDir &pluginsDir);

signals:
    //! Сигнал о загрузке плагина
    void loadedPlugin(QObject *plugin);

    //! Сигнал об удалении плагина
    void removedPlugin(QObject *plugin);

    //! Сигнал об окончании загрузки плагинов
    void endLoadingPlugins();

private slots:
    //! Удаляет указанный плагин
    void removePlugin(QObject *obj);

private:
    //! Структура файла с плагином
    struct FileList {
        QString filename; //! Имя файла
        bool lock;        //! Флаг блокировки загрузки файла
    };

    //! Экземпляр менеджера плагинов
    static PluginManager *m_instance;

    //! Настройки
    QSettings *m_settings;

    //! Список плагинов
    /*! В списке плагинов хранятся загруженные плагины, которые можно получить
     *  по интерфейсам
     */
    QMultiHash<QString, QObject *> m_interfaces;

    //! Каталог нахождения плагинов
    QDir m_pluginsDir;

    //! Список файлов в каталоге плагина
    std::vector<FileList> m_fileList;
};

}}

#endif // PLUGINMANAGER_H

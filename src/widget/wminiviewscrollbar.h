#ifndef WMINIVIEWSCROLLBAR_H
#define WMINIVIEWSCROLLBAR_H

#include <QAbstractItemModel>
#include <QPointer>
#include <QScrollBar>

class WMiniViewScrollBar : public QScrollBar
{
  public:
    WMiniViewScrollBar(QWidget* parent = nullptr);

    void setShowLetters(bool show);
    bool showLetters() const;

    void setSortColumn(int column);
    int sortColumn();
    
    void setRole(int role);
    int role();

    void setModel(QAbstractItemModel* model);

  protected:
    virtual void paintEvent(QPaintEvent* event);
    virtual void resizeEvent(QResizeEvent* pEvent);
    virtual void mouseMoveEvent(QMouseEvent* pEvent);
    virtual void mousePressEvent(QMouseEvent* pEvent);
    virtual void leaveEvent(QEvent*pEvent);

  private:
    struct CharPosition {
        QChar character;
        int position;
        bool bold;
    };
    
  private slots:
    void refreshCharMap();

  private:
    // The purpose of this function is to avoid computing all the sizes in the
    // paintEvent function which can block the GUI thread
    void computeLettersSize();
    void triggerUpdate();

    static int findSmallest(const QVector<CharPosition>& vector);
    static float interpolHeight(float current, float max1,
                                float max2);

    int m_sortColumn;
    int m_dataRole;
    bool m_showLetters;
    QVector<CharPosition> m_letters;
    QVector<CharPosition> m_computedSize;
    QPointer<QAbstractItemModel> m_pModel;
};

#endif // WMINIVIEWSCROLLBAR_H

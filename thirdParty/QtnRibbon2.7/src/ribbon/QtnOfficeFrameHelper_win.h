/****************************************************************************
**
** Qtitan Library by Developer Machines (Advanced OfficeFrameHelperWin for Qt)
** 
** Copyright (c) 2009-2012 Developer Machines (http://www.devmachines.com)
**           ALL RIGHTS RESERVED
** 
**  The entire contents of this file is protected by copyright law and
**  international treaties. Unauthorized reproduction, reverse-engineering
**  and distribution of all or any portion of the code contained in this
**  file is strictly prohibited and may result in severe civil and 
**  criminal penalties and will be prosecuted to the maximum extent 
**  possible under the law.
**
**  RESTRICTIONS
**
**  THE SOURCE CODE CONTAINED WITHIN THIS FILE AND ALL RELATED
**  FILES OR ANY PORTION OF ITS CONTENTS SHALL AT NO TIME BE
**  COPIED, TRANSFERRED, SOLD, DISTRIBUTED, OR OTHERWISE MADE
**  AVAILABLE TO OTHER INDIVIDUALS WITHOUT WRITTEN CONSENT
**  AND PERMISSION FROM DEVELOPER MACHINES
**
**  CONSULT THE END USER LICENSE AGREEMENT FOR INFORMATION ON
**  ADDITIONAL RESTRICTIONS.
**
****************************************************************************/
#ifndef QTN_OFFICEFRAMEHELPER_WIN_H
#define QTN_OFFICEFRAMEHELPER_WIN_H

#include <QObject>
#include <QSize>
#include <QRect>
#include <qt_windows.h>


#include "QtnOfficeFrameHelper.h"
#include "QtitanDef.h"


namespace Qtitan
{
    class StyleOptionFrame;
    class RibbonBar;
    /* OfficeFrameHelperWin */
    class OfficeFrameHelperWin : public QObject,
                                 public OfficeFrameHelper
    {
        Q_OBJECT
    public:
        OfficeFrameHelperWin(QWidget* parent = Q_NULL);
        virtual ~OfficeFrameHelperWin();

    public:
        virtual void enableOfficeFrame(QWidget* parent);
        void disableOfficeFrame();

        virtual bool isDwmEnabled() const;
        virtual bool isActive() const;

        virtual int getFrameBorder() const;
        virtual int titleBarSize() const;
        virtual int tabBarHeight() const;

        virtual void setHeaderRect(const QRect& rcHeader);
        virtual void setContextHeader(QList<ContextHeader*>* listContextHeaders);

        virtual QPixmap getFrameSmallIcon() const;
        virtual QString getSystemMenuString(uint item) const;

        virtual void drawTitleBar(QPainter* painter, const StyleOptionTitleBar& opt);
        virtual void fillSolidRect(QPainter* painter, const QRect& rect, QColor clr);
        virtual void drawDwmCaptionText(QPainter* painter, const QRect& rect, const QString& strWindowText, bool active);
        virtual QSize getSizeSystemIcon() const;
        virtual void resetIcon();

    public:
        bool collapseTopFrameStrut();
        virtual bool winEvent(MSG* message, long* result);

    private:
        static int frameSize() { return GetSystemMetrics(SM_CYSIZEFRAME); }
        static int captionSize() { return GetSystemMetrics(SM_CYCAPTION); }

    protected:
        void drawBlackRect(HDC hdc, const QRect &rect);

        DWORD getStyle(bool exStyle = false) const;
        void refreshFrameStyle();
        void updateFrameRegion();
        void updateFrameRegion(const QSize& szFrameRegion, bool bUpdate);
        bool isMDIMaximized() const;
        bool isTitleVisible() const;
        void initStyleOption(StyleOptionFrame* option);
        void redrawFrame();
        bool modifyStyle(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags);
        bool isFrameHasStatusBar(int* statusHeight = Q_NULL) const;
        HRGN calcFrameRegion(QSize sz);
        HFONT getCaptionFont(HANDLE hTheme);
        bool hitTestContextHeaders(const QPoint& point) const;
        bool isCompositionEnabled();
        bool resolveSymbols();

    protected:
        virtual bool eventFilter(QObject* obj, QEvent* event);

    public:
        static bool m_allowDwm;

        bool m_lockNCPaint;
        bool m_inUpdateFrame;
        bool m_inLayoutRequest;
        bool m_active;
        bool m_wasFullScreen;

    private:
        HICON m_hIcon;
        QWidget* m_frame;
        RibbonBar* m_ribbonBar;
        QList<ContextHeader*>* m_listContextHeaders;
        QSize m_szFrameRegion;
        QRect m_rcHeader;
        int m_collapseTop;
        int m_collapseBottom;
        int m_frameBorder;
        int m_borderSizeBotton;
        HWND m_hwndFrame;
        bool m_dwmEnabled;
        bool m_skipNCPaint;
        bool m_officeFrameEnabled;

    private:
        Q_DISABLE_COPY(OfficeFrameHelperWin)
    };

}; //namespace Qtitan


#endif // QTN_OFFICEFRAMEHELPER_WIN_H


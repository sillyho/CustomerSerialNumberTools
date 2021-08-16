#include "stdafx.h"
#include "CDateItem.h"


CDateItem::CDateItem(DateType dt)
{
     TypeDate = dt;
	 Type = ItemType::Date;
     YearCount=50;
     MonthCount = 12;
     DayCount =31;
     InitMap();
}
CDateItem::CDateItem()
{
    TypeDate = DateType::Year;
    Type = ItemType::Date;
    YearCount = 50;
    MonthCount = 12;
    DayCount = 31;
    InitMap();
}
CString CDateItem::ToString()
{
    CTime tmpTime = CTime::GetCurrentTime();
    if (TypeDate == DateType::Year)
    {
        if (!m_DateMapYear.Lookup(tmpTime.GetYear(), Value))
        {
            return  _T("");
        }
    }
    else if (TypeDate == DateType::Month)
    {
        if (!m_DateMapMonth.Lookup(tmpTime.GetMonth(), Value))
        {
            return  _T("");
        }
    }
    else if (TypeDate == DateType::Day)
    {
        if (!m_DateMapDay.Lookup(tmpTime.GetDay(), Value))
        {
            return  _T("");
        }
    }
    return Value;
}
void CDateItem::InitMap()
{
    CTime tmpTime = CTime::GetCurrentTime();
    int nCurYear = tmpTime.GetYear();
    m_DateMapYear.RemoveAll();
    CString tmpDate = _T("");
    for (int i = nCurYear; i < YearCount+ nCurYear; i++)
    {
        tmpDate.Format(_T("%04d"), i);
        m_DateMapYear.SetAt(i, tmpDate);
    }
    m_DateMapMonth.RemoveAll();
    for (int i = 1; i <= MonthCount; i++)
    {
        tmpDate.Format(_T("%02d"), i);
        m_DateMapMonth.SetAt(i, tmpDate);
    }

    m_DateMapDay.RemoveAll();
    for (int i = 1; i <= DayCount; i++)
    {
        tmpDate.Format(_T("%02d"), i);
        m_DateMapDay.SetAt(i, tmpDate);
    }
}
void CDateItem::Serialize(CArchive& archive)
{
    CObject::Serialize(archive);

    if (archive.IsStoring())
    {
        archive << Type  << TypeDate;
       
        //遍历CMap
        POSITION po = m_DateMapYear.GetStartPosition();
        int TmpKey = 0;
        CString TmpValue = _T("");
        while (po)
        {
            m_DateMapYear.GetNextAssoc(po, TmpKey, TmpValue);
            archive << TmpKey << TmpValue;
        }

        po = m_DateMapMonth.GetStartPosition();
        while (po)
        {
            m_DateMapMonth.GetNextAssoc(po, TmpKey, TmpValue);
            archive << TmpKey << TmpValue;
        }

        po = m_DateMapDay.GetStartPosition();
        while (po)
        {
            m_DateMapDay.GetNextAssoc(po, TmpKey, TmpValue);
            archive << TmpKey << TmpValue;
        }
    }
    else
    {
        int nType, nDateType;
        archive >> nType >> nDateType;
        Type = (ItemType)nType;
        TypeDate = (DateType)nDateType;
        m_DateMapYear.RemoveAll();
        m_DateMapMonth.RemoveAll();
        m_DateMapDay.RemoveAll();
        int nKey;
        CString sValue;
        for (int i = 0; i < YearCount; i++)
        {
            archive >> nKey >> sValue;
            m_DateMapYear.SetAt(nKey, sValue);
        }

        for (int i = 0; i < MonthCount; i++)
        {
            archive >> nKey >> sValue;
            m_DateMapMonth.SetAt(nKey, sValue);
        }

        for (int i = 0; i < DayCount; i++)
        {
            archive >> nKey >> sValue;
            m_DateMapDay.SetAt(nKey, sValue);
        }
    }
}
BOOL CDateItem::Plus(int nloop )
{
    return TRUE;
}
void CDateItem::Clear()
{
    m_DateMapDay.RemoveAll();
    m_DateMapMonth.RemoveAll();
    m_DateMapYear.RemoveAll();
}
void CDateItem::Clone(CItem& ct)
{
    ((CDateItem*)(&ct))->Type = this->Type;
    ((CDateItem*)(&ct))->TypeDate = this->TypeDate;
    ((CDateItem*)(&ct))->YearCount = this->YearCount;
    ((CDateItem*)(&ct))->MonthCount = this->MonthCount;
    ((CDateItem*)(&ct))->DayCount = this->DayCount;

    ((CDateItem*)(&ct))->m_DateMapYear.RemoveAll();
    //遍历CMap
    POSITION po = this->m_DateMapYear.GetStartPosition();
    int TmpKey = 0;
    CString TmpValue = _T("");
    while (po)
    {
        m_DateMapYear.GetNextAssoc(po, TmpKey, TmpValue);
        ((CDateItem*)(&ct))->m_DateMapYear.SetAt(TmpKey, TmpValue);
    }


    ((CDateItem*)(&ct))->m_DateMapMonth.RemoveAll();
    //遍历CMap
    po = this->m_DateMapMonth.GetStartPosition();
    while (po)
    {
        m_DateMapMonth.GetNextAssoc(po, TmpKey, TmpValue);
        ((CDateItem*)(&ct))->m_DateMapMonth.SetAt(TmpKey, TmpValue);
    }

    ((CDateItem*)(&ct))->m_DateMapDay.RemoveAll();
    //遍历CMap
    po = this->m_DateMapDay.GetStartPosition();
    while (po)
    {
        m_DateMapDay.GetNextAssoc(po, TmpKey, TmpValue);
        ((CDateItem*)(&ct))->m_DateMapDay.SetAt(TmpKey, TmpValue);
    }
}

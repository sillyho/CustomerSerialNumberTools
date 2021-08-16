#include "stdafx.h"
#include "CSerialItem.h"

CSerialItem::CSerialItem(CString collection, UINT len):m_CharacterCollection(collection), m_StringLength(len)
{
    m_curOctValue = 0;
    m_OctMinValue = 0;
    m_CharacterCollection = _T("0123456789");
    m_OctMaxValue = GetMax();
    Type = ItemType::SerialNumber;
}
CSerialItem::CSerialItem()
{
    Type = ItemType::SerialNumber;
}
CSerialItem::CSerialItem(CString collection, UINT len, CString cur , CString min , CString max , BOOL cir):
	m_CharacterCollection(collection), m_StringLength(len), m_bCirculate(cir)
{
	m_curOctValue = AnyToOct(cur);
	m_OctMinValue = AnyToOct(min);
	m_OctMaxValue = AnyToOct(max);
    Type = ItemType::SerialNumber;
}

CString CSerialItem::ToString()
{
    OctToAny();
    return Value;
}
void CSerialItem::Serialize(CArchive& archive)
{
    CObject::Serialize(archive);

    if (archive.IsStoring())
    {
        archive << Type << m_curOctValue<< m_OctMinValue<< m_OctMaxValue<< m_StringLength<< m_bCirculate<< m_CharacterCollection;
    }
    else
    {
        int nType;
        archive >> nType >> m_curOctValue >> m_OctMinValue >> m_OctMaxValue >> m_StringLength >> m_bCirculate >> m_CharacterCollection;
        Type = (ItemType)nType;
    }
}
void CSerialItem::OctToAny()
{
    CString strTmpData = _T("");
    ULONG lval = m_curOctValue;
    ULONG ltargeSys = m_CharacterCollection.GetLength();
    do
    {
        ULONG y = lval % ltargeSys;
        strTmpData= strTmpData+ m_CharacterCollection[y];
        lval = (ULONG)(lval/ ltargeSys);
    } while (lval > 0);
    Value = strTmpData.MakeReverse();
    for (int i = 0; i <= m_StringLength - Value.GetLength(); i++)
    {
        Value = m_CharacterCollection[0] + Value;
    }
}
CString CSerialItem::OctToAny(ULONG lval)
{
    CString strTmpData = _T("");
 
    ULONG ltargeSys = m_CharacterCollection.GetLength();
    do
    {
        ULONG y = lval % ltargeSys;
        strTmpData = strTmpData + m_CharacterCollection[y];
        lval = (ULONG)(lval / ltargeSys);
    } while (lval > 0);
    CString strData = strTmpData.MakeReverse();
    for (int i = 0; i < m_StringLength - strTmpData.GetLength(); i++)
    {
        strData = m_CharacterCollection[0] + strData;
    }
    return strData;
}
BOOL CSerialItem::Plus(int nloop )
{
    if (m_bCirculate)
    {
        if (m_curOctValue+nloop > m_OctMaxValue)
        {
            m_curOctValue = m_OctMinValue;
            return TRUE;
        }
    }
    else
    {
        if (m_curOctValue  > m_OctMaxValue)
        {
            return FALSE;
        }
    }
    m_curOctValue += nloop;

	return TRUE;
}
ULONG CSerialItem::AnyToOct(CString strAny)
{
    ULONG uValue = 0;
    if (strAny.GetLength() != m_StringLength)
        return 0;
    CString strAnyReverse = strAny.MakeReverse();
    UINT ltargetSys = m_CharacterCollection.GetLength();
    for (int i = 0; i < strAnyReverse.GetLength(); i++)
    {
        int nIndex = m_CharacterCollection.Find(strAnyReverse.GetAt(i));
        if (nIndex < 0)
            return 0;
        uValue += (ULONG)(nIndex*pow(ltargetSys, i));
    }
    return uValue;
}

ULONG CSerialItem::GetMax()
{
    ULONG umax = 0;
    UINT ltargetSys = m_CharacterCollection.GetLength();

    for (int i = 0; i < m_StringLength; i++)
    {
        umax+= (ULONG)((ltargetSys-1)*pow(ltargetSys, i));
    }
    return umax;
}
void  CSerialItem::Clear()
{
    
}

void CSerialItem::Clone(CItem& ct)
{
    ((CSerialItem*)(&ct))->Type = this->Type;
    ((CSerialItem*)(&ct))->m_curOctValue = this->m_curOctValue;
    ((CSerialItem*)(&ct))->m_OctMinValue = this->m_OctMinValue;
    ((CSerialItem*)(&ct))->m_OctMaxValue = this->m_OctMaxValue;
    ((CSerialItem*)(&ct))->m_StringLength = this->m_StringLength;
    ((CSerialItem*)(&ct))->m_bCirculate = this->m_bCirculate;
    ((CSerialItem*)(&ct))->m_CharacterCollection = this->m_CharacterCollection;
}
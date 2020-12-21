package com.example.test.servicelmpl;

import com.example.test.bean.BorrowInfo;
import com.example.test.mapper.BorrowInfoMapper;
import com.example.test.service.BorrowInfoService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Date;
import java.util.List;

@Service
public class BorrowInfoServiceImpl implements BorrowInfoService {


    @Autowired
    private BorrowInfoMapper borrowInfoMapper;


    @Override
    public List<BorrowInfo> getUnreturnInfo_By_ID(String ID) {
        return borrowInfoMapper.getUnreturnInfo_By_ID(ID);
    }

    @Override
    public List<BorrowInfo> getBorrowInfo_By_ID(String ID) {
        return borrowInfoMapper.getBorrowInfo_By_ID(ID) ;
    }

    @Override
    public int ReviewBookCondition(String ISBN) {
        return borrowInfoMapper.ReviewBookCondition(ISBN);
    }

    @Override
    public int ReviewBorrConditon(String StuID) {
        return borrowInfoMapper.ReviewBorrConditon(StuID);
    }

    @Override
    public boolean BorrowBook(String StuID, String ISBN, Date date) {
        return borrowInfoMapper.BorrowBook(StuID,ISBN,date);
    }

    @Override
    public boolean SetBorrowedBook(String ISBN) {
        return borrowInfoMapper.SetBorrowedBook(ISBN);
    }

    @Override
    public boolean SetBorrowedStudent(String StuID) {
        return borrowInfoMapper.SetBorrowedStudent(StuID);
    }

    @Override
    public boolean ReturnBook(String StuID, String ISBN, Date date) {
        return borrowInfoMapper.ReturnBook(StuID,ISBN,date);
    }

    @Override
    public boolean SetReturnedStudent(String StuID) {
        return borrowInfoMapper.SetReturnedStudent(StuID);
    }

    @Override
    public boolean SetReturnedBook(String ISBN) {
        return borrowInfoMapper.SetReturnedBook(ISBN);
    }

    @Override
    public int overdue(String id, String ISBN) {
        return borrowInfoMapper.overdue(id,ISBN);
    }

    @Override
    public int getOverdueDays(String id, String ISBN) {
        return borrowInfoMapper.getOverdueDays(id,ISBN);
    }

    @Override
    public int ReviewReturnStatus(String StuID, String ISBN) {
        return borrowInfoMapper.ReviewReturnStatus(StuID,ISBN);
    }

    @Override
    public boolean ReturnStatus(String StuID, String ISBN) {
        return borrowInfoMapper.ReturnStatus(StuID,ISBN);
    }

    @Override
    public int SetPenalty(int days, String stuid) {
        return borrowInfoMapper.SetPenalty(days,stuid);
    }
}

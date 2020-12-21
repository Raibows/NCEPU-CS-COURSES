<template>
  <el-row :gutter="20">
    <el-col :span="10" style="margin: 20px">
      <el-form ref="ruleForm" :model="ruleForm" :rules="rules" label-width="100px" class="demo-ruleForm">
        <el-form-item label="ISBN" prop="isbn" required>
          <el-input v-model="ruleForm.isbn" clearable />
        </el-form-item>
        <el-form-item label="书名" prop="bookName" required>
          <el-input v-model="ruleForm.bookName" clearable />
        </el-form-item>
        <el-form-item label="类型" prop="type" required>
          <el-input v-model="ruleForm.type" clearable />
        </el-form-item>
        <el-form-item label="作者" prop="author" required>
          <el-input v-model="ruleForm.author" clearable />
        </el-form-item>
        <el-form-item label="出版社" prop="publisher" required>
          <el-input v-model="ruleForm.publisher" clearable />
        </el-form-item>
        <el-form-item label="数量" prop="num" required>
          <el-input v-model="ruleForm.num" clearable />
        </el-form-item>
        <el-form-item label="出版时间" required>
          <el-col :span="11">
            <el-form-item prop="publishDate">
              <el-date-picker v-model="ruleForm.publishDate" type="date" placeholder="选择日期" style="width: 100%;" />
            </el-form-item>
          </el-col>
        </el-form-item>
        <el-form-item>
          <el-button type="primary" @click="submitForm('ruleForm')">录入</el-button>
          <el-button @click="resetForm('ruleForm')">重置</el-button>
        </el-form-item>
      </el-form>
    </el-col>

    <el-col :span="12" style="margin-top: 0px;margin-left: 20px">
      <h3 style="margin-left: 250px">验收清单</h3>
      <el-row>
        <el-table
          :data="checkData"
          border
          style="width: 100%;"
          height="260px"
        >
          <el-table-column
            fixed
            prop="isbn"
            label="isbn"
            width="100"
          />
          <el-table-column
            prop="bookSeller"
            label="出版社"
            width="120"
          />
          <el-table-column
            prop="bookName"
            label="书名"
            width="120"
          />
          <el-table-column
            prop="num"
            label="数量"
            width="120"
          />
          <el-table-column
            fixed="right"
            label="操作"
            width="200"
          >
            <template slot-scope="scope">
              <el-button type="primary" size="small" @click="addCheckTo(scope.row)">导入</el-button>
              <el-button type="primary" size="small" @click="addCheckToTemporary(scope.row,'采访清单')">录入临时列表</el-button>
            </template>
          </el-table-column>
        </el-table>
      </el-row>
      <el-row style="margin-top: 20px;">
        <el-col :span="12" :offset="6">
          <el-pagination
            :current-page="checkCurrentPage"
            :page-sizes="[5, 10, 20]"
            :page-size="checkPageSize"
            layout="total, sizes, prev, pager, next, jumper"
            :total="checkTotal"
            @size-change="handleCheckSizeChange"
            @current-change="handleCheckCurrentChange"
          />
        </el-col>
      </el-row>
    </el-col>

    <el-col :span="12" style="margin-top: 20px;margin-left: 20px">
      <h3 style="margin-left: 250px">校友捐赠目录</h3>
      <el-row>
        <el-table
          :data="donateData"
          border
          style="width: 100%;"
          height="260px"
        >
          <el-table-column
            fixed
            prop="id"
            label="学号"
            width="80"
          />
          <el-table-column
            prop="name"
            label="名字"
            width="100"
          />
          <el-table-column
            prop="isbn"
            label="isbn"
            width="100"
          />
          <el-table-column
            prop="major"
            label="专业"
            width="120"
          />
          <el-table-column
            prop="bookName"
            label="书名"
            width="120"
          />
          <el-table-column
            prop="num"
            label="数量"
            width="100"
          />
          <el-table-column
            fixed="right"
            label="操作"
            width="200"
          >
            <template slot-scope="scope">
              <el-button type="primary" size="small" @click="addDonationTo(scope.row)">导入</el-button>
              <el-button type="primary" size="small" @click="addCheckToTemporary(scope.row,'捐赠清单')">录入临时列表</el-button>
            </template>
          </el-table-column>
        </el-table>
      </el-row>
      <el-row style="margin-top: 20px;">
        <el-col :span="12" :offset="6">
          <el-pagination
            :current-page="donateCurrentPage"
            :page-sizes="[5, 10, 20]"
            :page-size="donatePageSize"
            layout="total, sizes, prev, pager, next, jumper"
            :total="donateTotal"
            @size-change="handleDonateSizeChange"
            @current-change="handleDonateCurrentChange"
          />
        </el-col>
      </el-row>
    </el-col>
  </el-row>
</template>

<script>
import { addToTemporary, searchCheckList, searchDonation, addBook } from '../../../api/catalogue'

export default {
  name: 'CatalogueCatalogue',
  data() {
    return {
      ruleForm: {
        isbn: '',
        bookName: '',
        type: '',
        author: '',
        publisher: '',
        publishDate: '',
        delivery: false,
        desc: '',
        num: ''
      },
      checkCurrentPage: 1,
      checkPageSize: 10,
      checkTotal: '',
      donateCurrentPage: 1,
      donatePageSize: 10,
      donateTotal: '',
      rules: {
        isbn: [
          { required: true, message: '请输入ISBN', trigger: 'blur' },
          { min: 13, max: 13, message: '长度为13位', trigger: 'blur' }
        ],
        bookName: [
          { required: true, message: '请输入书名', trigger: 'blur' },
          { min: 1, max: 13, trigger: 'blur' }
        ],
        type: [
          { required: true, message: '请输入类型', trigger: 'blur' },
          { min: 1, max: 13, trigger: 'blur' }
        ],
        author: [
          { required: true, message: '请输入作者名', trigger: 'blur' },
          { min: 1, max: 13, trigger: 'blur' }
        ],
        publisher: [
          { required: true, message: '请输入出版社名字', trigger: 'blur' },
          { min: 1, max: 20, message: '请输入正确名称', trigger: 'blur' }
        ],
        num: [{
          required: true, message: '请输入数量', trigger: 'blur'
        }],
        publishDate: [
          { type: 'date', required: true, message: '请选择日期', trigger: 'change' }
        ]
      },
      checkData: [
        {
          isbn: '',
          bookSeller: '',
          bookName: '',
          num: 10
        }
      ],
      donateData: [
        {
          id: '',
          isbn: '',
          name: '',
          major: '',
          bookName: '',
          num: 10
        }
      ]
    }
  },
  created() {
    this.searchCheck()
    this.searchDonation()
  },
  methods: {
    submitForm(formName) {
      this.$refs[formName].validate((valid) => {
        if (valid) {
          if (this.ruleForm.type === '编程') {
            this.ruleForm.type = 1
          } else if (this.ruleForm.type === '青春') {
            this.ruleForm.type = 2
          } else if (this.ruleForm.type === '历史') {
            this.ruleForm.type = 3
          } else {
            this.ruleForm.type = 4
          }
          this.ruleForm.publishDate = this.ruleForm.publishDate.getFullYear() + '-' + this.ruleForm.publishDate.getMonth() +
            '-' + this.ruleForm.publishDate.getDay()
          console.log(this.ruleForm)
          addBook({
            isbn: this.ruleForm.isbn,
            bookName: this.ruleForm.bookName,
            type: this.ruleForm.type,
            author: this.ruleForm.author,
            publisher: this.ruleForm.publisher,
            publishDate: this.ruleForm.publishDate,
            num: this.ruleForm.num,
            canBorrow: true,
            url: 'http'
          }).then(response => {
            this.$message({
              type: 'success',
              message: response.msg
            })
          })
        }
      })
    },
    resetForm(formName) {
      this.$refs[formName].resetFields()
    },
    addCheckTo(col) {
      this.ruleForm.isbn = col.isbn
      this.ruleForm.bookName = col.bookName
      this.ruleForm.publisher = col.bookSeller
      this.ruleForm.num = col.num
    },
    addDonationTo(row) {
      this.ruleForm.isbn = row.isbn
      this.ruleForm.bookName = row.bookName
      this.ruleForm.num = row.num
    },
    addCheckToTemporary(row, op) {
      addToTemporary({ isbn: row.isbn, bookName: row.bookName, opName: op }).then(response => {
        this.$message({
          type: 'success',
          message: response.msg
        })
      })
    },
    searchCheck() {
      searchCheckList({
        all: '', page: this.checkCurrentPage - 1, size: this.checkPageSize }).then(response => {
        this.checkData = response.data.content
        this.checkCurrentPage = response.data.pageable.pageNumber + 1
        this.checkPageSize = response.data.pageable.pageSize
        this.checkTotal = response.data.totalElements
      })
    },
    searchDonation() {
      searchDonation({ page: this.donateCurrentPage - 1, size: this.donatePageSize }).then(response => {
        this.donateData = response.data.content
        this.donateCurrentPage = response.data.pageable.pageNumber + 1
        this.donatePageSize = response.data.pageable.pageSize
        this.donateTotal = response.data.totalElements
      })
    },
    handleCheckSizeChange(val) {
      this.checkPageSize = val
      this.searchCheck()
    },
    handleCurrentChange(val) {
      this.checkCurrentPage = val
      this.searchCheck()
    },
    handleDonateSizeChange(val) {
      this.donatePageSize = val
      this.searchDonation()
    },
    handleDonateCurrentChange(val) {
      this.donateCurrentPage = val
      this.searchDonation()
    }
  }
}
</script>

<style lang="scss" scoped>

</style>

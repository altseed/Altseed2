
#pragma once



namespace Altseed2 {

	class MediaPlayer
    : public ReferenceObject {
private:
protected:
    MediaPlayer() {}
    virtual ~MediaPlayer() {}
    bool isLoopingMode = false;

public:
    /**
		@brief	�f�����Đ�����B
		@param	isLoopingMode	���[�v�Đ����邩?
	*/
    virtual bool Play(bool isLoopingMode) = 0;

    /**
		@brief	�f����ǂݍ��ށB
		@param	path	�t�@�C���̃p�X
		@note
		H264�𐄏�����B
	*/
    virtual bool Load(const char16_t* path) = 0;

    /**
		@brief	���݂̉f�����e�N�X�`���ɏ������ށB
		@param	target	�������ݐ�
		@note
		�f���ƃe�N�X�`���̉𑜓x�͓������K�v������B
	*/
    virtual bool WriteToTexture2D(Texture2D* target) = 0;

    /**
		@brief	�ǂݍ��񂾉f���̑傫�����擾����B
	*/
    virtual Vector2DI GetSize() const = 0;

    /**
		@brief	���ݍĐ����̉f���̃t���[���ԍ����擾����B
	*/
    virtual int32_t GetCurrentFrame() const = 0;
};

}